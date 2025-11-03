import tensorflow as tf
from tensorflow.keras import datasets, layers, models

# 데이터 불러오기 (MNIST)
(x_train, y_train), (x_test, y_test) = datasets.mnist.load_data()
x_train = x_train.reshape(-1, 28, 28, 1).astype("float32") / 255.0
x_test = x_test.reshape(-1, 28, 28, 1).astype("float32") / 255.0

# LeNet-5 모델 정의
model = models.Sequential([
    layers.Conv2D(6, (5,5), activation='tanh', input_shape=(28,28,1)),
    layers.AveragePooling2D((2,2)),
    layers.Conv2D(16, (5,5), activation='tanh'),
    layers.AveragePooling2D((2,2)),
    layers.Conv2D(120, (5,5), activation='tanh'),
    layers.Flatten(),
    layers.Dense(84, activation='tanh'),
    layers.Dense(10, activation='softmax')
])

# 컴파일 및 학습
model.compile(optimizer='adam',
              loss='sparse_categorical_crossentropy',
              metrics=['accuracy'])
history = model.fit(x_train, y_train, epochs=10,
                    batch_size=128, validation_split=0.1)

# 평가 및 저장
test_loss, test_acc = model.evaluate(x_test, y_test)
print("MNIST LeNet-5 정확도:", test_acc)
model.save("lenet5_mnist.h5")
