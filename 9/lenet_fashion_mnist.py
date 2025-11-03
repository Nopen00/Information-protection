from tensorflow.keras import datasets, layers, models

# Fashion-MNIST 데이터 불러오기
(x_train, y_train), (x_test, y_test) = datasets.fashion_mnist.load_data()

# 데이터 전처리
x_train = x_train.reshape(-1, 28, 28, 1).astype("float32") / 255.0
x_test = x_test.reshape(-1, 28, 28, 1).astype("float32") / 255.0

# LeNet 모델 정의 (28x28x1 입력) - 수정된 버전
model = models.Sequential([
    layers.Conv2D(6, (5,5), activation='tanh', input_shape=(28,28,1)),
    layers.AveragePooling2D((2,2)),
    layers.Conv2D(16, (5,5), activation='tanh'),
    layers.AveragePooling2D((2,2)),
    layers.Flatten(),
    layers.Dense(120, activation='tanh'),
    layers.Dense(84, activation='tanh'),
    layers.Dense(10, activation='softmax')  # Fashion-MNIST: 10개 클래스
])

# 컴파일 및 학습
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])

print("=" * 50)
print("Fashion-MNIST LeNet 학습 시작")
print("=" * 50)
history = model.fit(x_train, y_train, epochs=10,
                    batch_size=128, validation_split=0.1, verbose=1)

# 평가
test_loss, test_acc = model.evaluate(x_test, y_test, verbose=0)
print("\n" + "=" * 50)
print(f"Fashion-MNIST 테스트 정확도: {test_acc:.4f}")
print("=" * 50)

# 모델 저장
model.save("lenet_fashion_mnist.h5")
print("모델이 'lenet_fashion_mnist.h5'로 저장되었습니다.")

