"""
Deep Belief Network (DBN) 구현
RBM을 사용한 사전 학습 후 분류기로 파인튜닝
"""

import tensorflow as tf
import numpy as np
import matplotlib.pyplot as plt
from tensorflow.keras import layers, models, optimizers

# ============================================================================
# 데이터 로딩 및 전처리
# ============================================================================
(xtr, ytr), (xte, yte) = tf.keras.datasets.mnist.load_data()
xtr = (xtr.astype("float32") / 255.).reshape(-1, 784)
xte = (xte.astype("float32") / 255.).reshape(-1, 784)

# 베르누이 RBM을 위한 이산화 (옵션)
# xtr = (xtr > 0.5).astype("float32")
# xte = (xte > 0.5).astype("float32")

BATCH = 128
train_ds = tf.data.Dataset.from_tensor_slices(xtr).shuffle(10000).batch(BATCH)


# ============================================================================
# RBM 클래스 정의
# ============================================================================
class RBM(tf.keras.Model):
    """
    Bernoulli-Bernoulli RBM with Contrastive Divergence (CD-k)
    
    Attributes:
        n_visible: 가시층 노드 수
        n_hidden: 은닉층 노드 수
        k: CD-k의 k 값 (기본값: 1)
        W: 가중치 행렬 (n_visible, n_hidden)
        vb: 가시층 편향 (n_visible,)
        hb: 은닉층 편향 (n_hidden,)
    """
    
    def __init__(self, n_visible, n_hidden, k=1):
        super().__init__()
        self.n_visible = n_visible
        self.n_hidden = n_hidden
        self.k = k

        # Xavier 초기화
        limit = np.sqrt(6. / (n_visible + n_hidden))
        self.W = tf.Variable(
            tf.random.uniform([n_visible, n_hidden], -limit, limit),
            name="W"
        )
        self.vb = tf.Variable(tf.zeros([n_visible]), name="vb")
        self.hb = tf.Variable(tf.zeros([n_hidden]), name="hb")

    @staticmethod
    def _sigm(x):
        """시그모이드 함수"""
        return tf.math.sigmoid(x)

    def sample_h(self, v):
        """가시층 v로부터 은닉층 h 샘플링"""
        p_h = self._sigm(tf.matmul(v, self.W) + self.hb)
        return p_h, tf.cast(tf.random.uniform(tf.shape(p_h)) < p_h, tf.float32)

    def sample_v(self, h):
        """은닉층 h로부터 가시층 v 샘플링"""
        p_v = self._sigm(tf.matmul(h, tf.transpose(self.W)) + self.vb)
        return p_v, tf.cast(tf.random.uniform(tf.shape(p_v)) < p_v, tf.float32)

    def cd_loss_and_grads(self, v0):
        """
        Contrastive Divergence를 사용한 손실 및 그래디언트 계산
        
        Args:
            v0: 입력 가시층 데이터
            
        Returns:
            recon_loss: 재구성 손실
            [dW, dvb, dhb]: 가중치, 가시층 편향, 은닉층 편향의 그래디언트
        """
        with tf.GradientTape() as tape:
            # Positive phase
            p_h0, h0 = self.sample_h(v0)

            # Gibbs sampling (k steps)
            vk, hk = v0, h0
            for _ in range(self.k):
                pvk, vk = self.sample_v(hk)
                phk, hk = self.sample_h(vk)

            # CD-k 손실 계산
            pos = tf.matmul(tf.transpose(v0), p_h0)
            neg = tf.matmul(tf.transpose(vk), phk)

            # 재구성 손실 (모니터링용)
            recon_loss = tf.reduce_mean(
                tf.keras.losses.binary_crossentropy(v0, pvk)
            )

            # 그래디언트 계산
            dW = (pos - neg) / tf.cast(tf.shape(v0)[0], tf.float32)
            dvb = tf.reduce_mean(v0 - vk, axis=0)
            dhb = tf.reduce_mean(p_h0 - phk, axis=0)

        return recon_loss, [dW, dvb, dhb]

    def fit_rbm(self, dataset, epochs=10, lr=1e-3):
        """
        RBM 학습
        
        Args:
            dataset: 학습 데이터셋
            epochs: 에포크 수
            lr: 학습률
        """
        opt = tf.keras.optimizers.Adam(lr)
        for ep in range(1, epochs + 1):
            losses = []
            for v0 in dataset:
                loss, [dW, dvb, dhb] = self.cd_loss_and_grads(v0)
                opt.apply_gradients([
                    (-dW, self.W),
                    (-dvb, self.vb),
                    (-dhb, self.hb)
                ])
                losses.append(loss.numpy())
            print(f"[RBM] epoch {ep:02d}  recon={np.mean(losses):.4f}")

    def transform(self, X, batch=512):
        """
        특징 추출: p(h|v) 계산
        
        Args:
            X: 입력 데이터
            batch: 배치 크기
            
        Returns:
            은닉층 확률 분포
        """
        H = []
        for i in range(0, X.shape[0], batch):
            v = tf.convert_to_tensor(X[i:i+batch], dtype=tf.float32)
            p_h, _ = self.sample_h(v)
            H.append(p_h.numpy())
        return np.concatenate(H, axis=0)

    def generate(self, n=16, steps=200):
        """
        Gibbs 샘플링을 사용한 데이터 생성
        
        Args:
            n: 생성할 샘플 수
            steps: Gibbs 샘플링 스텝 수
            
        Returns:
            생성된 가시층 샘플
        """
        h = tf.cast(tf.random.uniform([n, self.n_hidden]) < 0.5, tf.float32)
        v = tf.cast(tf.random.uniform([n, self.n_visible]) < 0.5, tf.float32)
        for _ in range(steps):
            _, h = self.sample_h(v)
            pv, v = self.sample_v(h)
        return pv.numpy()


# ============================================================================
# DBN 사전 학습: RBM 층별 학습
# ============================================================================
print("=" * 60)
print("1층 RBM 학습")
print("=" * 60)
rbm1 = RBM(784, 256, k=1)
rbm1.fit_rbm(train_ds, epochs=10, lr=1e-3)

print("\n" + "=" * 60)
print("2층 RBM 학습")
print("=" * 60)
H1 = rbm1.transform(xtr)
train_ds_h1 = tf.data.Dataset.from_tensor_slices(H1).shuffle(10000).batch(BATCH)
rbm2 = RBM(256, 128, k=1)
rbm2.fit_rbm(train_ds_h1, epochs=10, lr=1e-3)


# ============================================================================
# 사전 학습된 가중치로 분류기 구성 및 파인튜닝
# ============================================================================
print("\n" + "=" * 60)
print("분류기 구성 및 파인튜닝")
print("=" * 60)

# 사전 학습된 가중치로 Dense 레이어 초기화
dense1 = layers.Dense(256, activation="sigmoid")
dense2 = layers.Dense(128, activation="sigmoid")
dense1.build((None, 784))
dense2.build((None, 256))
dense1.set_weights([rbm1.W.numpy(), rbm1.hb.numpy()])
dense2.set_weights([rbm2.W.numpy(), rbm2.hb.numpy()])

# 분류기 모델 구성
clf = models.Sequential([
    layers.Input(shape=(784,)),
    dense1,
    dense2,
    layers.Dense(10, activation="softmax")
])

clf.compile(
    optimizer=optimizers.Adam(1e-3),
    loss="sparse_categorical_crossentropy",
    metrics=["accuracy"]
)

# 파인튜닝
hist = clf.fit(
    xtr, ytr,
    validation_data=(xte, yte),
    epochs=10,
    batch_size=128,
    verbose=1
)


# ============================================================================
# 생성된 샘플 시각화
# ============================================================================
print("\n" + "=" * 60)
print("생성된 샘플 시각화")
print("=" * 60)

samples = rbm1.generate(n=16, steps=200)
fig, axs = plt.subplots(4, 4, figsize=(4, 4))
for i, ax in enumerate(axs.ravel()):
    ax.imshow(samples[i].reshape(28, 28), cmap="gray")
    ax.axis("off")
plt.tight_layout()
plt.show()
