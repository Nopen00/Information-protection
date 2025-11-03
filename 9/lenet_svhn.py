from tensorflow.keras import layers, models
import numpy as np
import scipy.io

# SVHN 데이터 다운로드 및 로드
def load_svhn():
    print("SVHN 데이터 다운로드 중...")
    import urllib.request
    import tarfile
    import os
    
    # SVHN 데이터 URL
    url = "http://ufldl.stanford.edu/housenumbers/train_32x32.mat"
    test_url = "http://ufldl.stanford.edu/housenumbers/test_32x32.mat"
    
    # 다운로드 디렉토리
    data_dir = "./svhn_data"
    os.makedirs(data_dir, exist_ok=True)
    
    train_path = os.path.join(data_dir, "train_32x32.mat")
    test_path = os.path.join(data_dir, "test_32x32.mat")
    
    # 데이터 다운로드 (없는 경우에만)
    if not os.path.exists(train_path):
        print("학습 데이터 다운로드 중...")
        urllib.request.urlretrieve(url, train_path)
    
    if not os.path.exists(test_path):
        print("테스트 데이터 다운로드 중...")
        urllib.request.urlretrieve(test_url, test_path)
    
    # 데이터 로드
    train_data = scipy.io.loadmat(train_path)
    test_data = scipy.io.loadmat(test_path)
    
    x_train = train_data['X']
    y_train = train_data['y'].flatten()
    x_test = test_data['X']
    y_test = test_data['y'].flatten()
    
    # 데이터 형태 변환 (H, W, C, N) -> (N, H, W, C)
    x_train = np.transpose(x_train, (3, 0, 1, 2))
    x_test = np.transpose(x_test, (3, 0, 1, 2))
    
    # 레이블을 0-9로 변환 (10은 0으로)
    y_train[y_train == 10] = 0
    y_test[y_test == 10] = 0
    
    return (x_train, y_train), (x_test, y_test)

# SVHN 데이터 불러오기
(x_train, y_train), (x_test, y_test) = load_svhn()

# 데이터 전처리
x_train = x_train.astype("float32") / 255.0
x_test = x_test.astype("float32") / 255.0

# LeNet 모델 정의 (32x32x3 입력)
model = models.Sequential([
    layers.Conv2D(6, (5,5), activation='tanh', input_shape=(32,32,3)),
    layers.AveragePooling2D((2,2)),
    layers.Conv2D(16, (5,5), activation='tanh'),
    layers.AveragePooling2D((2,2)),
    layers.Conv2D(120, (5,5), activation='tanh'),
    layers.Flatten(),
    layers.Dense(84, activation='tanh'),
    layers.Dense(10, activation='softmax')  # SVHN: 10개 클래스
])

# 컴파일 및 학습
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

print("=" * 50)
print("SVHN LeNet 학습 시작")
print("=" * 50)
history = model.fit(x_train, y_train, epochs=10,
                    batch_size=128, validation_split=0.1, verbose=1)

# 평가
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
print("\n" + "=" * 50)
print(f"SVHN 테스트 정확도: {test_acc:.4f}")
print("=" * 50)

# 모델 저장
model.save("lenet_svhn.h5")
print("모델이 'lenet_svhn.h5'로 저장되었습니다.")

