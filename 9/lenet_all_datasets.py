"""
LeNet 재현 실습 - 모든 데이터셋 실험
6가지 데이터셋에 LeNet 모델을 적용하는 통합 코드
"""

from tensorflow.keras import datasets, layers, models
import numpy as np
import os
import time
import matplotlib.pyplot as plt
# 한글 폰트 설정 (한글 표시 문제 시 주석 해제)
# plt.rcParams['font.family'] = 'Malgun Gothic'
plt.rcParams['axes.unicode_minus'] = False  # 마이너스 기호 깨짐 방지

def load_stl10():
    """STL-10 데이터셋 로드 (현재는 건너뜀)"""
    print("경고: STL-10은 Keras에 포함되어 있지 않아 건너뜁니다.")
    return None


def load_svhn():
    """SVHN 데이터셋 로드 (현재는 건너뜀)"""
    print("경고: SVHN은 scipy 라이브러리가 필요하여 건너뜁니다.")
    return None


def create_lenet_model_mnist(num_classes):
    """28x28 이미지용 LeNet 모델 (MNIST, Fashion-MNIST)"""
    model = models.Sequential([
        layers.Conv2D(6, (5,5), activation='tanh', input_shape=(28,28,1)),
        layers.AveragePooling2D((2,2)),
        layers.Conv2D(16, (5,5), activation='tanh'),
        layers.AveragePooling2D((2,2)),
        layers.Flatten(),  # 세 번째 Conv 없이 Flatten
        layers.Dense(120, activation='tanh'),
        layers.Dense(84, activation='tanh'),
        layers.Dense(num_classes, activation='softmax')
    ])
    return model


def create_lenet_model_large(input_shape, num_classes):
    """32x32 이상 이미지용 LeNet 모델 (CIFAR, SVHN)"""
    model = models.Sequential([
        layers.Conv2D(6, (5,5), activation='tanh', input_shape=input_shape),
        layers.AveragePooling2D((2,2)),
        layers.Conv2D(16, (5,5), activation='tanh'),
        layers.AveragePooling2D((2,2)),
        layers.Conv2D(120, (5,5), activation='tanh'),
        layers.Flatten(),
        layers.Dense(84, activation='tanh'),
        layers.Dense(num_classes, activation='softmax')
    ])
    return model


def create_lenet_model_stl10(num_classes):
    """96x96 이미지용 LeNet 모델 (STL-10)"""
    model = models.Sequential([
        layers.Conv2D(6, (5,5), activation='tanh', input_shape=(96,96,3)),
        layers.AveragePooling2D((2,2)),
        layers.Conv2D(16, (5,5), activation='tanh'),
        layers.AveragePooling2D((2,2)),
        layers.Conv2D(120, (5,5), activation='tanh'),
        layers.AveragePooling2D((2,2)),  # 추가 pooling
        layers.Flatten(),
        layers.Dense(84, activation='tanh'),
        layers.Dense(num_classes, activation='softmax')
    ])
    return model


def train_and_evaluate_model(model, x_train, y_train, x_test, y_test, 
                             dataset_name, epochs=10):
    """모델 학습 및 평가"""
    model.compile(optimizer='adam',
                  loss='sparse_categorical_crossentropy',
                  metrics=['accuracy'])
    
    print("\n" + "=" * 60)
    print(f"{dataset_name} LeNet 학습 시작")
    print("=" * 60)
    
    start_time = time.time()
    history = model.fit(x_train, y_train, epochs=epochs,
                        batch_size=128, validation_split=0.1, 
                        verbose=1)
    train_time = time.time() - start_time
    
    test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
    
    print("\n" + "=" * 60)
    print(f"{dataset_name} 결과:")
    print(f"  테스트 정확도: {test_acc:.4f}")
    print(f"  학습 시간: {train_time:.2f}초")
    print("=" * 60 + "\n")
    
    # 모델 저장
    model.save(f"lenet_{dataset_name.lower().replace('-', '_')}.h5")
    
    return test_acc, train_time, history


# 실험 결과 저장
results = []
histories = []

# 1. MNIST
print("\n[1/6] MNIST 데이터셋")
(x_train, y_train), (x_test, y_test) = datasets.mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1).astype("float32") / 255.0
x_test = x_test.reshape(-1, 28, 28, 1).astype("float32") / 255.0
model = create_lenet_model_mnist(10)
test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                          x_test, y_test, "MNIST")
results.append(("MNIST", test_acc, train_time))
histories.append(("MNIST", history))

# 2. Fashion-MNIST
print("\n[2/6] Fashion-MNIST 데이터셋")
(x_train, y_train), (x_test, y_test) = datasets.fashion_mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1).astype("float32") / 255.0
x_test = x_test.reshape(-1, 28, 28, 1).astype("float32") / 255.0
model = create_lenet_model_mnist(10)
test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                          x_test, y_test, "Fashion-MNIST")
results.append(("Fashion-MNIST", test_acc, train_time))
histories.append(("Fashion-MNIST", history))

# 3. CIFAR-10
print("\n[3/6] CIFAR-10 데이터셋")
(x_train, y_train), (x_test, y_test) = datasets.cifar10.load_data()
x_train = x_train.astype("float32") / 255.0
x_test = x_test.astype("float32") / 255.0
model = create_lenet_model_large((32, 32, 3), 10)
test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                          x_test, y_test, "CIFAR-10")
results.append(("CIFAR-10", test_acc, train_time))
histories.append(("CIFAR-10", history))

# 4. CIFAR-100
print("\n[4/6] CIFAR-100 데이터셋")
(x_train, y_train), (x_test, y_test) = datasets.cifar100.load_data()
x_train = x_train.astype("float32") / 255.0
x_test = x_test.astype("float32") / 255.0
model = create_lenet_model_large((32, 32, 3), 100)
test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                          x_test, y_test, "CIFAR-100")
results.append(("CIFAR-100", test_acc, train_time))
histories.append(("CIFAR-100", history))

# 5. STL-10
print("\n[5/6] STL-10 데이터셋")
stl10_data = load_stl10()
if stl10_data is not None:
    (x_train, y_train), (x_test, y_test) = stl10_data
    x_train = x_train.astype("float32") / 255.0
    x_test = x_test.astype("float32") / 255.0
    model = create_lenet_model_stl10(10)
    test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                              x_test, y_test, "STL-10")
    results.append(("STL-10", test_acc, train_time))
    histories.append(("STL-10", history))
else:
    print("STL-10 데이터셋을 건너뜁니다.")

# 6. SVHN
print("\n[6/6] SVHN 데이터셋")
svhn_data = load_svhn()
if svhn_data is not None:
    (x_train, y_train), (x_test, y_test) = svhn_data
    x_train = x_train.astype("float32") / 255.0
    x_test = x_test.astype("float32") / 255.0
    model = create_lenet_model_large((32, 32, 3), 10)
    test_acc, train_time, history = train_and_evaluate_model(model, x_train, y_train, 
                                                              x_test, y_test, "SVHN")
    results.append(("SVHN", test_acc, train_time))
    histories.append(("SVHN", history))
else:
    print("SVHN 데이터셋을 건너뜁니다.")

# 최종 결과 출력
print("\n" + "=" * 60)
print("전체 실험 결과 요약")
print("=" * 60)
print(f"{'데이터셋':<15} {'정확도':<10} {'학습 시간(초)':<15}")
print("-" * 60)
for dataset, acc, time_taken in results:
    print(f"{dataset:<15} {acc:.4f}    {time_taken:>10.2f}")
print("=" * 60)

# 그래프 생성
if len(histories) > 0:
    print("\nCreating training curves graph...")
    num_datasets = len(histories)
    cols = 3
    rows = (num_datasets + cols - 1) // cols  # 올림 처리
    
    fig, axes = plt.subplots(rows, cols, figsize=(18, 6*rows))
    fig.suptitle('LeNet Training Curves Comparison', fontsize=16, fontweight='bold')
    
    # axes를 항상 2D 배열로 만들기
    if rows == 1:
        axes = axes.reshape(1, -1)
    
    for idx, (dataset, history) in enumerate(histories):
        row = idx // cols
        col = idx % cols
        ax = axes[row, col]
        
        epochs = range(1, len(history.history['accuracy']) + 1)
        ax.plot(epochs, history.history['accuracy'], 'b-', label='Train Accuracy', linewidth=2)
        ax.plot(epochs, history.history['val_accuracy'], 'r-', label='Val Accuracy', linewidth=2)
        ax.set_title(f'{dataset}', fontsize=12, fontweight='bold')
        ax.set_xlabel('Epoch')
        ax.set_ylabel('Accuracy')
        ax.legend()
        ax.grid(True, alpha=0.3)
    
    # 빈 subplot 숨기기
    for idx in range(num_datasets, rows * cols):
        row = idx // cols
        col = idx % cols
        fig.delaxes(axes[row, col])
    
    plt.tight_layout()
    plt.savefig('lenet_training_curves.png', dpi=300, bbox_inches='tight')
    print("Graph saved as 'lenet_training_curves.png'")

# 정확도 비교 막대 그래프
fig2, ax2 = plt.subplots(figsize=(12, 6))
datasets = [r[0] for r in results]
accuracies = [r[1] for r in results]
colors = ['skyblue', 'lightcoral', 'lightgreen', 'plum', 'gold', 'lightsalmon']

bars = ax2.bar(datasets, accuracies, color=colors[:len(datasets)])
ax2.set_ylabel('Accuracy', fontsize=12)
ax2.set_title('LeNet Test Accuracy Comparison by Dataset', fontsize=14, fontweight='bold')
ax2.set_ylim(0, 1)
ax2.grid(True, alpha=0.3, axis='y')

# 막대 위에 값 표시
for bar, acc in zip(bars, accuracies):
    height = bar.get_height()
    ax2.text(bar.get_x() + bar.get_width()/2., height + 0.01,
             f'{acc:.3f}', ha='center', va='bottom', fontweight='bold')

plt.xticks(rotation=45, ha='right')
plt.tight_layout()
plt.savefig('lenet_accuracy_comparison.png', dpi=300, bbox_inches='tight')
print("Graph saved as 'lenet_accuracy_comparison.png'")

plt.show()

