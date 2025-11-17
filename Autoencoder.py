{
  "nbformat": 4,
  "nbformat_minor": 0,
  "metadata": {
    "colab": {
      "provenance": [],
      "authorship_tag": "ABX9TyMGBY3M6EK28pXBhavsHpjm",
      "include_colab_link": true
    },
    "kernelspec": {
      "name": "python3",
      "display_name": "Python 3"
    },
    "language_info": {
      "name": "python"
    }
  },
  "cells": [
    {
      "cell_type": "markdown",
      "metadata": {
        "id": "view-in-github",
        "colab_type": "text"
      },
      "source": [
        "<a href=\"https://colab.research.google.com/github/Nopen00/Information-protection/blob/main/Autoencoder.py\" target=\"_parent\"><img src=\"https://colab.research.google.com/assets/colab-badge.svg\" alt=\"Open In Colab\"/></a>"
      ]
    },
    {
      "cell_type": "code",
      "execution_count": 1,
      "metadata": {
        "colab": {
          "base_uri": "https://localhost:8080/",
          "height": 1000
        },
        "id": "kSpwQ1-eh0_0",
        "outputId": "3076897b-9df0-48f1-bf60-dbbd9e689ff9"
      },
      "outputs": [
        {
          "output_type": "stream",
          "name": "stdout",
          "text": [
            "Downloading data from https://storage.googleapis.com/tensorflow/tf-keras-datasets/mnist.npz\n",
            "\u001b[1m11490434/11490434\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m0s\u001b[0m 0us/step\n"
          ]
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1mModel: \"functional\"\u001b[0m\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\">Model: \"functional\"</span>\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n",
              "┃\u001b[1m \u001b[0m\u001b[1mLayer (type)                   \u001b[0m\u001b[1m \u001b[0m┃\u001b[1m \u001b[0m\u001b[1mOutput Shape          \u001b[0m\u001b[1m \u001b[0m┃\u001b[1m \u001b[0m\u001b[1m      Param #\u001b[0m\u001b[1m \u001b[0m┃\n",
              "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━┩\n",
              "│ input_layer (\u001b[38;5;33mInputLayer\u001b[0m)        │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m1\u001b[0m)      │             \u001b[38;5;34m0\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d (\u001b[38;5;33mConv2D\u001b[0m)                 │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m32\u001b[0m)     │           \u001b[38;5;34m320\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_1 (\u001b[38;5;33mConv2D\u001b[0m)               │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m14\u001b[0m, \u001b[38;5;34m14\u001b[0m, \u001b[38;5;34m64\u001b[0m)     │        \u001b[38;5;34m18,496\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_2 (\u001b[38;5;33mConv2D\u001b[0m)               │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m64\u001b[0m)       │        \u001b[38;5;34m36,928\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_3 (\u001b[38;5;33mConv2D\u001b[0m)               │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m64\u001b[0m)       │        \u001b[38;5;34m36,928\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ flatten (\u001b[38;5;33mFlatten\u001b[0m)               │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m3136\u001b[0m)           │             \u001b[38;5;34m0\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ dense (\u001b[38;5;33mDense\u001b[0m)                   │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m32\u001b[0m)             │       \u001b[38;5;34m100,384\u001b[0m │\n",
              "└─────────────────────────────────┴────────────────────────┴───────────────┘\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\">┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n",
              "┃<span style=\"font-weight: bold\"> Layer (type)                    </span>┃<span style=\"font-weight: bold\"> Output Shape           </span>┃<span style=\"font-weight: bold\">       Param # </span>┃\n",
              "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━┩\n",
              "│ input_layer (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">InputLayer</span>)        │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">1</span>)      │             <span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2D</span>)                 │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">32</span>)     │           <span style=\"color: #00af00; text-decoration-color: #00af00\">320</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_1 (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2D</span>)               │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">14</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">14</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)     │        <span style=\"color: #00af00; text-decoration-color: #00af00\">18,496</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_2 (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2D</span>)               │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)       │        <span style=\"color: #00af00; text-decoration-color: #00af00\">36,928</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_3 (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2D</span>)               │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)       │        <span style=\"color: #00af00; text-decoration-color: #00af00\">36,928</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ flatten (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Flatten</span>)               │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">3136</span>)           │             <span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ dense (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Dense</span>)                   │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">32</span>)             │       <span style=\"color: #00af00; text-decoration-color: #00af00\">100,384</span> │\n",
              "└─────────────────────────────────┴────────────────────────┴───────────────┘\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Total params: \u001b[0m\u001b[38;5;34m193,056\u001b[0m (754.12 KB)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Total params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">193,056</span> (754.12 KB)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Trainable params: \u001b[0m\u001b[38;5;34m193,056\u001b[0m (754.12 KB)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Trainable params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">193,056</span> (754.12 KB)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Non-trainable params: \u001b[0m\u001b[38;5;34m0\u001b[0m (0.00 B)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Non-trainable params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> (0.00 B)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1mModel: \"functional_1\"\u001b[0m\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\">Model: \"functional_1\"</span>\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n",
              "┃\u001b[1m \u001b[0m\u001b[1mLayer (type)                   \u001b[0m\u001b[1m \u001b[0m┃\u001b[1m \u001b[0m\u001b[1mOutput Shape          \u001b[0m\u001b[1m \u001b[0m┃\u001b[1m \u001b[0m\u001b[1m      Param #\u001b[0m\u001b[1m \u001b[0m┃\n",
              "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━┩\n",
              "│ input_layer_1 (\u001b[38;5;33mInputLayer\u001b[0m)      │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m32\u001b[0m)             │             \u001b[38;5;34m0\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ dense_1 (\u001b[38;5;33mDense\u001b[0m)                 │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m3136\u001b[0m)           │       \u001b[38;5;34m103,488\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ reshape (\u001b[38;5;33mReshape\u001b[0m)               │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m64\u001b[0m)       │             \u001b[38;5;34m0\u001b[0m │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose                │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m7\u001b[0m, \u001b[38;5;34m64\u001b[0m)       │        \u001b[38;5;34m36,928\u001b[0m │\n",
              "│ (\u001b[38;5;33mConv2DTranspose\u001b[0m)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_1              │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m14\u001b[0m, \u001b[38;5;34m14\u001b[0m, \u001b[38;5;34m64\u001b[0m)     │        \u001b[38;5;34m36,928\u001b[0m │\n",
              "│ (\u001b[38;5;33mConv2DTranspose\u001b[0m)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_2              │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m32\u001b[0m)     │        \u001b[38;5;34m18,464\u001b[0m │\n",
              "│ (\u001b[38;5;33mConv2DTranspose\u001b[0m)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_3              │ (\u001b[38;5;45mNone\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m28\u001b[0m, \u001b[38;5;34m1\u001b[0m)      │           \u001b[38;5;34m289\u001b[0m │\n",
              "│ (\u001b[38;5;33mConv2DTranspose\u001b[0m)               │                        │               │\n",
              "└─────────────────────────────────┴────────────────────────┴───────────────┘\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\">┏━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━━━━━━━━━━┳━━━━━━━━━━━━━━━┓\n",
              "┃<span style=\"font-weight: bold\"> Layer (type)                    </span>┃<span style=\"font-weight: bold\"> Output Shape           </span>┃<span style=\"font-weight: bold\">       Param # </span>┃\n",
              "┡━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━━━━━━━━━━╇━━━━━━━━━━━━━━━┩\n",
              "│ input_layer_1 (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">InputLayer</span>)      │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">32</span>)             │             <span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ dense_1 (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Dense</span>)                 │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">3136</span>)           │       <span style=\"color: #00af00; text-decoration-color: #00af00\">103,488</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ reshape (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Reshape</span>)               │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)       │             <span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose                │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">7</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)       │        <span style=\"color: #00af00; text-decoration-color: #00af00\">36,928</span> │\n",
              "│ (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2DTranspose</span>)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_1              │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">14</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">14</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">64</span>)     │        <span style=\"color: #00af00; text-decoration-color: #00af00\">36,928</span> │\n",
              "│ (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2DTranspose</span>)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_2              │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">32</span>)     │        <span style=\"color: #00af00; text-decoration-color: #00af00\">18,464</span> │\n",
              "│ (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2DTranspose</span>)               │                        │               │\n",
              "├─────────────────────────────────┼────────────────────────┼───────────────┤\n",
              "│ conv2d_transpose_3              │ (<span style=\"color: #00d7ff; text-decoration-color: #00d7ff\">None</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">28</span>, <span style=\"color: #00af00; text-decoration-color: #00af00\">1</span>)      │           <span style=\"color: #00af00; text-decoration-color: #00af00\">289</span> │\n",
              "│ (<span style=\"color: #0087ff; text-decoration-color: #0087ff\">Conv2DTranspose</span>)               │                        │               │\n",
              "└─────────────────────────────────┴────────────────────────┴───────────────┘\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Total params: \u001b[0m\u001b[38;5;34m196,097\u001b[0m (766.00 KB)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Total params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">196,097</span> (766.00 KB)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Trainable params: \u001b[0m\u001b[38;5;34m196,097\u001b[0m (766.00 KB)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Trainable params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">196,097</span> (766.00 KB)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "\u001b[1m Non-trainable params: \u001b[0m\u001b[38;5;34m0\u001b[0m (0.00 B)\n"
            ],
            "text/html": [
              "<pre style=\"white-space:pre;overflow-x:auto;line-height:normal;font-family:Menlo,'DejaVu Sans Mono',consolas,'Courier New',monospace\"><span style=\"font-weight: bold\"> Non-trainable params: </span><span style=\"color: #00af00; text-decoration-color: #00af00\">0</span> (0.00 B)\n",
              "</pre>\n"
            ]
          },
          "metadata": {}
        },
        {
          "output_type": "stream",
          "name": "stdout",
          "text": [
            "Epoch 1/5\n",
            "\u001b[1m469/469\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m186s\u001b[0m 385ms/step - loss: 0.0468 - val_loss: 0.0068\n",
            "Epoch 2/5\n",
            "\u001b[1m469/469\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m174s\u001b[0m 372ms/step - loss: 0.0064 - val_loss: 0.0052\n",
            "Epoch 3/5\n",
            "\u001b[1m469/469\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m176s\u001b[0m 376ms/step - loss: 0.0048 - val_loss: 0.0042\n",
            "Epoch 4/5\n",
            "\u001b[1m469/469\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m200s\u001b[0m 371ms/step - loss: 0.0042 - val_loss: 0.0039\n",
            "Epoch 5/5\n",
            "\u001b[1m469/469\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m174s\u001b[0m 371ms/step - loss: 0.0039 - val_loss: 0.0037\n",
            "\u001b[1m313/313\u001b[0m \u001b[32m━━━━━━━━━━━━━━━━━━━━\u001b[0m\u001b[37m\u001b[0m \u001b[1m10s\u001b[0m 33ms/step\n"
          ]
        },
        {
          "output_type": "display_data",
          "data": {
            "text/plain": [
              "<Figure size 2000x400 with 20 Axes>"
            ],
            "image/png": "iVBORw0KGgoAAAANSUhEUgAABiEAAAE/CAYAAAAg+mBzAAAAOnRFWHRTb2Z0d2FyZQBNYXRwbG90bGliIHZlcnNpb24zLjEwLjAsIGh0dHBzOi8vbWF0cGxvdGxpYi5vcmcvlHJYcgAAAAlwSFlzAAAPYQAAD2EBqD+naQAAQ/BJREFUeJzt3We8FeXZL+ABRKSJgKAgCipiASu2WGJNrKDYSzTRxBI1MfaGUTFqjvpiSazvidEQY4ktVlSssR8bahQNGkQFFaVIFQTOp/eczNxP3MvNmrX2huv6lPv/e/bat2GYmbUe1twtFi5cuDADAAAAAACospb1bgAAAAAAAFg82YQAAAAAAABKYRMCAAAAAAAohU0IAAAAAACgFDYhAAAAAACAUtiEAAAAAAAASmETAgAAAAAAKIVNCAAAAAAAoBRLVbJowYIF2YQJE7KOHTtmLVq0KLsnmrCFCxdm06dPz3r27Jm1bFnuHpbjjv9Rq+POMce/c9xRa66x1INzHbXmXEc9ONdRD447as01lnqo9LiraBNiwoQJ2corr1y15mj+Pvroo6xXr16l/g7HHUVlH3eOOVIcd9Saayz14FxHrTnXUQ/OddSD445ac42lHho67iraFuvYsWPVGmLxUItjwnFHUdnHhGOOFMcdteYaSz0411FrznXUg3Md9eC4o9ZcY6mHho6JijYhfK2GolocE447iso+JhxzpDjuqDXXWOrBuY5ac66jHpzrqAfHHbXmGks9NHRMGEwNAAAAAACUwiYEAAAAAABQCpsQAAAAAABAKWxCAAAAAAAApbAJAQAAAAAAlMImBAAAAAAAUAqbEAAAAAAAQClsQgAAAAAAAKWwCQEAAAAAAJTCJgQAAAAAAFCKperdACyuTj755JC1bds2ZOutt16u3meffSp6/WuuuSZXP//882HNiBEjKnotAAAAAIAy+CYEAAAAAABQCpsQAAAAAABAKWxCAAAAAAAApbAJAQAAAAAAlMJgaqiC2267LWSVDpguWrBgQUXrjjrqqFy94447hjVPPfVUyMaPH9+ovqCoX79+IRszZkzIjj/++JD97ne/K6Unmq727dvn6ksuuSSsKZ7XsizLXnnllVy97777hjUffvjhInYHAAAsqTp37hyyVVZZpVGvlXpvcsIJJ+Tqt956K6x57733QjZ69OhG9QBNkW9CAAAAAAAApbAJAQAAAAAAlMImBAAAAAAAUAqbEAAAAAAAQCkMpoZGKA6ibuwQ6iyLg3wffvjhsGa11VYL2aBBg3L16quvHtYcfPDBIbvooou+a4uQtOGGG4YsNVj9448/rkU7NHE9evTI1UcccURYkzp+Bg4cmKt33333sOaqq65axO5objbaaKOQ3XXXXSHr06dPDbr5dj/84Q9z9TvvvBPWfPTRR7Vqh2aieJ+XZVl27733huy4444L2bXXXpur58+fX73GKE337t1Ddvvtt4fsueeeC9n111+fq8eNG1e1vqqpU6dOIfv+97+fq0eOHBnWzJs3r7SegMXfbrvtlqsHDx4c1my77bYh69u3b6N+X2rAdO/evXN1mzZtKnqtVq1aNaoHaIp8EwIAAAAAACiFTQgAAAAAAKAUNiEAAAAAAIBSmAkBDdh4441DNmTIkAZ/7h//+EfIUs8e/OKLL3L1jBkzwpqll146ZC+88EKuXn/99cOarl27NtgnNNYGG2wQspkzZ4bs7rvvrkE3NCXdunUL2U033VSHTlhc7bTTTiGr9Nm6tVZ8tv/hhx8e1hxwwAG1aocmqnjPdvXVV1f0c7///e9DdsMNN+Tq2bNnN74xStO5c+dcnXrvkJqh8Nlnn4WsKc6ASPX+yiuvhKx4z1CcBZVlWTZ27NjqNcZ3tuyyy4asOGdwwIABYc2OO+4YMvM9WBTFOZjHHntsWJOaO9e2bdtc3aJFi+o2VtCvX79SXx+aK9+EAAAAAAAASmETAgAAAAAAKIVNCAAAAAAAoBQ2IQAAAAAAgFI02cHU++yzT8hSA2YmTJiQq+fMmRPW3HzzzSH79NNPQ2bgFSk9evQIWXGQUWqQXGpo5sSJExvVw0knnRSyddZZp8Gfe+CBBxr1+yClOHDuuOOOC2tGjBhRq3ZoIn75y1+GbM899wzZpptuWpXf9/3vfz9kLVvGf1MxevTokD399NNV6YHaWmqpeLu666671qGTxikOYj3xxBPDmvbt24ds5syZpfVE01M8t/Xq1auin7vllltClno/RH0tv/zyIbvttttydZcuXcKa1IDyX/ziF9VrrERDhw4N2aqrrhqyo446Kld7T15fBx98cMguuOCCkK288soNvlZqoPWXX37ZuMYgi9fG448/vk6d/H9jxowJWerzIRYfffv2DVnqOj9kyJBcve2224Y1CxYsCNm1114bsmeffTZXN9drpW9CAAAAAAAApbAJAQAAAAAAlMImBAAAAAAAUAqbEAAAAAAAQCma7GDqiy++OGR9+vRp1GsVh11lWZZNnz49ZE1xeMzHH38cstT/Ny+//HIt2lki3XfffSErDqJJHU+TJ0+uWg8HHHBAyFq3bl2114dKrLXWWrk6NUi1OGSRxd9ll10WstSArWrZa6+9Kso+/PDDkO2///65ujgwmKZpu+22C9n3vve9kKXuj5qCzp075+p11lknrGnXrl3IDKZefLVp0yZkZ511VqNea8SIESFbuHBho16L8my00UYhSw2oLBo2bFgJ3ZSjf//+ufqkk04Ka+6+++6QuXesn+KQ3yzLsssvvzxkXbt2DVkl55nf/e53ITvuuONydTXfM9M0FQf2poZJF4fuZlmWjRw5MmRff/11rp42bVpYk7p/Kr5vfeSRR8Kat956K2QvvvhiyF577bVcPXv27Ip6oHkYMGBAyIrnrdR7z9Rg6sbabLPNQvbNN9/k6nfffTeseeaZZ0JW/Ps2d+7cRexu0fgmBAAAAAAAUAqbEAAAAAAAQClsQgAAAAAAAKVosjMhjjjiiJCtt956IXvnnXdy9dprrx3WVPoMzs033zxXf/TRR2HNyiuvHLJKFJ/flWVZNmnSpJD16NGjwdcaP358yMyEqK3Us8ar5ZRTTglZv379Gvy51PMKUxk01qmnnpqrU38PnIsWbw8++GDIWrYs998zfPnll7l6xowZYU3v3r1Dtuqqq4bspZdeytWtWrVaxO4oQ/FZrLfccktY8/7774fswgsvLK2nRbHHHnvUuwWamHXXXTdkAwcObPDnUu8nHnrooar0RPV07949ZHvvvXeDP/fTn/40ZKn3i01Bcf5DlmXZqFGjGvy51EyI1Gw9auPkk08OWZcuXar2+sVZXFmWZTvvvHOuvuCCC8Ka1CyJej/HnMqkZgYW5y+sv/76Yc2QIUMqev0XXnghV6c+6xs3blzIVllllVydmr1a5kw76i/1efKxxx4bstR5a9lll23w9T/55JOQ/f3vf8/V//rXv8Ka4mcsWZaeW7jpppvm6tS5etdddw3Z6NGjc/W1114b1tSSb0IAAAAAAAClsAkBAAAAAACUwiYEAAAAAABQCpsQAAAAAABAKZrsYOrHHnusoqxo5MiRFb1+586dQ7bBBhvk6tQwkE022aSi1y+aM2dOyN57772QFQdtp4aNpIYx0nztvvvuuXrYsGFhzdJLLx2yzz//PFefccYZYc2sWbMWsTuWVH369AnZxhtvnKtT57CZM2eW1RJ1sM022+TqNddcM6xJDXFr7GC31KCs4jC7adOmhTXbb799yM4666wGf9/Pf/7zkF1zzTUN/hzlGjp0aK5ODTksDrbMsvTQ8lpL3bcV/x4ZfEglQ4pTiudDmqb/+q//CtmPfvSjkBXfa/71r38tradq23rrrUO2wgor5Oobb7wxrPnzn/9cVktUoHfv3rn6sMMOq+jn3njjjZB99tlnuXrHHXes6LU6deqUq1PDsW+++eaQffrppxW9PrWT+oziL3/5S8iKg6gvvPDCsKaSwfYpqSHUKePHj2/U69N8XXfddbk6Nfx8+eWXr+i1ip9Fv/nmm2HNmWeeGbLU58BFW2yxRchS71FvuOGGXF38/DrL4nk5y7LsqquuytV33nlnWDNp0qSG2qwa34QAAAAAAABKYRMCAAAAAAAohU0IAAAAAACgFDYhAAAAAACAUjTZwdRlmzJlSsieeOKJBn+ukuHYlUoNpSsOzE4NPLntttuq1gP1Vxz2mxrwlFI8Dp566qmq9QTFQaoptRxgRPlSw8hvvfXWXF3p8K6UDz/8MFenhmKdd955IZs1a9Z3fu0sy7IjjzwyZN26dcvVF198cVizzDLLhOz3v/99rp43b16DPVGZffbZJ2S77rprrh47dmxY8/LLL5fW06JIDUQvDqJ+8sknw5qpU6eW1BFN0fe///0G18ydOzdkqeOLpmfhwoUhSw2knzBhQq5O/ZnXWtu2bUOWGrZ5zDHHhKz433344YdXrzGqojjItGPHjmHN3//+95Cl3hcU75cOPPDAsCZ17Ky++uq5esUVVwxr/va3v4Vsl112CdnkyZNDRnk6dOiQq88444ywZvfddw/ZF198kasvvfTSsKaS+33IsvR7tVNPPTVkP/vZz3J1ixYtwprU5xnXXHNNyC655JJcPXPmzAb7rFTXrl1D1qpVq5Cde+65uXrkyJFhTe/evavWV1l8EwIAAAAAACiFTQgAAAAAAKAUNiEAAAAAAIBS2IQAAAAAAABKscQOpq617t27h+zqq68OWcuW+X2hYcOGhTUGMDVf99xzT8h++MMfNvhzf/rTn0I2dOjQarQESeuuu26Da1JDfWm+lloq3hI0dhD1U089FbIDDjggVxeH1C2K1GDqiy66KGTDhw/P1e3atQtrUsf1vffem6vff//979oi/8G+++4bsuKfS+p+qSlIDXM/+OCDQzZ//vxc/Zvf/CasMex88bXFFltUlBWlhh6+/vrr1WiJJmK33XbL1Y888khYkxpanxqa2VjFgcPbbrttWLP55ptX9Fp33HFHNVqiRG3atMnVqSHql112WUWvNWfOnFz9xz/+MaxJXeNXW221Bl87NaS4KQxuX9Ltueeeufr0008Pa8aPHx+yrbfeOldPmzatqn2xZEldp0455ZSQFQdRf/LJJ2HN3nvvHbKXXnqp8c0VFAdMr7zyymFN6rO+Bx98MGSdO3du8Pelhm+PGDEiV6fuK2rJNyEAAAAAAIBS2IQAAAAAAABKYRMCAAAAAAAohZkQNXLssceGrFu3biGbMmVKrn733XdL64ly9ejRI2SpZwAXn82Zek566vnRM2bMWITu4P9LPev3sMMOC9lrr72Wqx999NHSeqL5ePnll0N2+OGHh6yaMyAqUZzjkGXxef2bbLJJrdohy7JOnTqFrJJnjVfz+efVdOSRR4YsNUflnXfeydVPPPFEaT3R9DT2PNNUj3sadsUVV4Rsu+22C1nPnj1z9fe///2wJvV858GDBy9Cd9/++qkZASkffPBByM4888yq9ER5DjzwwAbXFGeVZFl6rmElNt5440b93AsvvBAy733rr5J5RsX3i1mWZR9//HEZ7bCEKs5ZyLI4fy3lm2++Cdlmm20Wsn322Sdka621VoOvP3v27JCtvfba31pnWfo98gorrNDg70v57LPPQlb8LLHec+h8EwIAAAAAACiFTQgAAAAAAKAUNiEAAAAAAIBS2IQAAAAAAABKYTB1CbbccsuQnX766RX97J577pmr33rrrWq0RB3ceeedIevatWuDP/fnP/85ZO+//35VeoKUHXfcMWRdunQJ2ciRI3P1nDlzSuuJpqFly4b/rUJqoFdTkBrmWfzvqeS/L8uy7Nxzz83VhxxySKP7WpK1adMmZCuttFLIbrnlllq0s8hWX331ita5l1uyVTqYderUqbnaYOrm65VXXgnZeuutF7INNtggV++8885hzSmnnBKySZMmheymm276Dh3+fyNGjMjVo0ePrujnnnvuuZB5v9L0Fa+vqSHnm2yy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4OSTT87VPXr0CGv++c9/huzCCy/M1QaWU0177LFHyFZYYYVcXc0BYjRNO+ywQ66ePHlyWNOqVauQtWvXLmTFgVc33nhjWHPPPfd8twa/xRVXXBGyn/zkJ7k6dZxPnDgxZGeeeWbV+iKveF7Jsizbe++9c/UHH3wQ1owYMaK0nhbF4MGDQ7bsssvm6nfeeadW7dBE/fCHPwxZcZDmV199FdbcddddpfVE9Wy11VYhW7BgQci+/PLLWrSzyIYOHRqyo446KmSffPJJrj7ppJNK64nGGThwYK5efvnlw5rUNSp1T/XII4/k6uLA6SzLsg033DBk66+/fq5O/X054ogjQnb22WeHjPr65S9/GbLUvfXtt9+eq72HpNquvPLKkO277765unXr1mHNfffdF7LrrrsuZGUObi4Or86yLNt8881D1qZNm1zdqVOnsCY1+Lr4vrz4OrXmmxAAAAAAAEApbEIAAAAAAAClsAkBAAAAAACUwiYEAAAAAABQCoOp6+iYY44JWdeuXXP18OHDa9UONXDOOeeEbMcdd2zw51IDOO++++6q9AQpu+22W8hmzJiRqx9++OFatUMNFK8/WZZla665Zq5ODfRKZX/4wx9CVhxelxqcVU2XXXZZyAYNGpSrV1pppbDmwAMPDNnvf//7XD1hwoRF7I7/ceKJJ4asT58+ubo53Qttt912IZs/f36ufvTRR2vVDk3AWmutFbI11lgjZMXB1B9++GFYUxwES9P0xRdfhCx1rdx5551z9c033xzWPPPMMyH7/PPPQ9aqVatc3blz57CmY8eOISsOJl5ttdXCmtTg4OLvy7L43uS9994La6ivVVddNVfPnTs3rLn//vtDVsm5J3VvVLz+ZVk8dlLH0gYbbNDg76P2ioN+DzjggLAmda4rDqaGRTFgwICQ7bnnniErHotvvPFGWJMakl7Nzzjat2+fq1PvE/bee++QbbTRRiErDqIuDpzOsixbaqn4Ef8999zzrXWt+SYEAAAAAABQCpsQAAAAAABAKWxCAAAAAAAApTATokZOOeWUkKWeufn222/n6muvvba0nijX+uuvH7LBgweHrPisutdffz2sST3bHMq02Wabheyrr77K1Y8//nit2qEG+vfvH7LiM6XbtGkT1owePTpkp59+esjKngFR9NFHH4Xsk08+ydXFZ2FnWZb17t07ZOuuu26u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\n"
          },
          "metadata": {}
        }
      ],
      "source": [
        "import numpy as np\n",
        "from tensorflow.keras.datasets import mnist\n",
        "from tensorflow.keras.layers import Input, Dense, Flatten, Reshape, Conv2D, Conv2DTranspose\n",
        "from tensorflow.keras.models import Model\n",
        "from tensorflow.keras import backend as K\n",
        "\n",
        "# MNIST 데이터를 읽고 신경망에 입력할 준비\n",
        "(x_train,y_train), (x_test,y_test)=mnist.load_data()\n",
        "x_train=x_train.astype('float32')/255.\n",
        "x_test=x_test.astype('float32')/255.\n",
        "x_train=np.reshape(x_train, (len(x_train),28,28,1))\n",
        "x_test=np.reshape(x_test, (len(x_test),28,28,1))\n",
        "\n",
        "zdim=32 # 잠복 공간의 차원\n",
        "\n",
        "# 오토인코더의 인코더 부분 설계\n",
        "encoder_input=Input(shape=(28,28,1))\n",
        "x=Conv2D(32, (3,3), activation='relu',padding='same', strides=(1,1))(encoder_input)\n",
        "x=Conv2D(64, (3,3), activation='relu',padding='same', strides=(2,2))(x)\n",
        "x=Conv2D(64, (3,3), activation='relu',padding='same', strides=(2,2))(x)\n",
        "x=Conv2D(64, (3,3), activation='relu',padding='same', strides=(1,1))(x)\n",
        "x=Flatten()(x)\n",
        "encoder_output=Dense(zdim)(x)\n",
        "model_encoder=Model(encoder_input, encoder_output)\n",
        "model_encoder.summary()\n",
        "\n",
        "# 오토인코더의 디코더 부분 설계\n",
        "decoder_input=Input(shape=(zdim,))\n",
        "x=Dense(3136)(decoder_input)\n",
        "x=Reshape((7,7,64))(x)\n",
        "x=Conv2DTranspose(64, (3,3), activation='relu', padding='same', strides=(1,1))(x)\n",
        "x=Conv2DTranspose(64, (3,3), activation='relu', padding='same', strides=(2,2))(x)\n",
        "x=Conv2DTranspose(32, (3,3), activation='relu', padding='same', strides=(2,2))(x)\n",
        "x=Conv2DTranspose(1, (3,3), activation='relu', padding='same', strides=(1,1))(x)\n",
        "decoder_output=x\n",
        "model_decoder=Model(decoder_input, decoder_output)\n",
        "model_decoder.summary()\n",
        "\n",
        "# 인코더와 디코더를 결합하여 오토인코더 모델 구축\n",
        "model_input=encoder_input\n",
        "model_output=model_decoder(encoder_output)\n",
        "model=Model(model_input,model_output)\n",
        "\n",
        "# 오토인코더 학습\n",
        "model.compile(optimizer='Adam', loss='mse')\n",
        "model.fit(x_train,x_train, epochs=5,batch_size=128, shuffle=True, validation_data=(x_test,x_test))\n",
        "\n",
        "# 복원 실험 1: x_test를 복원하는 예측 실험\n",
        "decoded_img=model.predict(x_test)\n",
        "\n",
        "import matplotlib.pyplot as plt\n",
        "\n",
        "n=10\n",
        "plt.figure(figsize=(20, 4))\n",
        "for i in range(n):\n",
        "    plt.subplot(2, n, i+1)\n",
        "    plt.imshow(x_test[i].reshape(28, 28), cmap='gray')\n",
        "    plt.xticks([]); plt.yticks([])\n",
        "    plt.subplot(2, n, i + n+1)\n",
        "    plt.imshow(decoded_img[i].reshape(28, 28),cmap='gray')\n",
        "    plt.xticks([]); plt.yticks([])\n",
        "plt.show()\n"
      ]
    }
  ]
}