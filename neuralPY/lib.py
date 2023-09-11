import tensorflow as tf
import numpy as np
from tensorflow import keras

def VvodNormalize(first, second, third, fourth):
	input_data = []
	first_min = 1
	first_max = 100
	second_min = 0.1
	second_max = 1
	third_min = 3
	third_max = 15
	fourth_min = 0.1
	fourth_max = 0.4
	input_data += [(first-first_min)/(first_max-first_min),
		(second-second_min)/(second_max-second_min),
		(third-third_min)/(third_max-third_min),
		(-fourth-fourth_min)/(fourth_max-fourth_min)]
	return input_data

def FileNormalize(data):
	input_data = []
	for line in data.split("\n"):
		temp_data = line.split(";")
		input_data += [[float(temp_data[0]),
						float(temp_data[1]),
						float(temp_data[2]),
						float(temp_data[3])]]
	first_max = input_data[0][0]; second_max = input_data[0][1]; third_max = input_data[0][2];
	first_min = input_data[0][0]; second_min = input_data[0][1]; third_min = input_data[0][2];
	fourth_max = input_data[0][3];
	fourth_min = input_data[0][3];
	for i in range(1, len(input_data)):
		if (first_max < input_data[i][0]):
			first_max = input_data[i][0]
		if (second_max < input_data[i][1]):
			second_max = input_data[i][1]
		if (third_max < input_data[i][2]):
			third_max = input_data[i][2]
		if (fourth_max > input_data[i][3]):
			fourth_max = input_data[i][3]
		if (first_min > input_data[i][0]):
			first_min = input_data[i][0]
		if (second_min > input_data[i][1]):
			second_min = input_data[i][1]
		if (third_min > input_data[i][2]):
			third_min = input_data[i][2]
		if (fourth_min < input_data[i][3]):
			fourth_min = input_data[i][3]

	fourth_min = -fourth_min
	fourth_max = -fourth_max
	for x in input_data:
		x[0] = (x[0]-first_min)/(first_max-first_min)
		x[1] = (x[1]-second_min)/(second_max-second_min)
		x[2] = (x[2]-third_min)/(third_max-third_min)
		x[3] = (-x[3]-fourth_min)/(fourth_max-fourth_min)
	return input_data
