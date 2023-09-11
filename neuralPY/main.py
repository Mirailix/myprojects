import tensorflow as tf
import numpy as np
from random import shuffle
from tensorflow import keras
from lib import *

input_size = 4
hidden_size_1 = 128
hidden_size_2 = 64
output_size = 4

model = keras.models.load_model("")

model.compile(optimizer = tf.train.AdamOptimizer(),
              loss = 'mean_squared_error',#loss = 'sparse_categorical_crossentropy',
              metrics = ['accuracy'])

train_data = FileImport("", input_size)
shuffle(train_data)
test_data = train_data[430:]
train_data = train_data[:430]

train_input = np.array([x[0] for x in train_data])
train_output = np.array([x[1] for x in train_data])
test_input = np.array([x[0] for x in test_data])
test_output = np.array([x[1] for x in test_data])

def VvodWork(first, second, third, fourth):
    input_list = []
    input_list = np.array([VvodNormalize(first, second, third, fourth)])
    predictions = model.predict(input_list)
    return predictions

def FileWork(data):
    input_list = []
    input_list = np.array(FileNormalize(data))
    predictions = model.predict(input_list)
    return predictions
