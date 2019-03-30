import unittest
import pedsp.algorithm as algorithm
import numpy as np
from random import randint

from utiltity import generate_inputs


class TestAlgorithmMethods(unittest.TestCase):

    __number_inputs = 10
    __minimum_size = 0
    __maximum_size = 1000

    def test_scale(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            factor = randint(0, 5)
            generated = algorithm.scale(data, factor)
            reference = data * factor
            np.testing.assert_array_almost_equal(generated, reference)

    def test_scale_clip(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            factor = randint(0, 5)
            minimum = randint(self.__minimum_size, self.__maximum_size)
            maximum = randint(minimum, self.__maximum_size)
            generated = algorithm.scale_clip(data, factor, minimum, maximum)
            reference = np.clip(data * factor, minimum, maximum)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_clip(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            minimum = randint(self.__minimum_size, self.__maximum_size)
            maximum = randint(minimum, self.__maximum_size)
            generated = algorithm.clip(data,  minimum, maximum)
            reference = np.clip(data, minimum, maximum)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_round(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = algorithm.round(data)
            reference = np.round(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_floor(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = algorithm.floor(data)
            reference = np.floor(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_trunc(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = algorithm.trunc(data)
            reference = np.trunc(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_abs(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = algorithm.abs(data)
            reference = np.abs(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_normalize(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = algorithm.normalize(data)
            reference = data / np.max(np.abs(data)).item()
            np.testing.assert_array_almost_equal(generated, reference)

    def test_concatenate(self):
        data = generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size)
        for i in range(0, len(data)):
            first = data[randint(0, len(data) - 1)]
            second = data[randint(0, len(data) - 1)]
            generated = algorithm.concatenate(first, second)
            reference = np.concatenate((first, second))
            np.testing.assert_array_almost_equal(generated, reference)

    def test_pad(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            size = randint(len(data), self.__maximum_size)
            generated = algorithm.pad(data, size)
            reference = np.pad(data, (0, size - len(data) % size), mode='constant', constant_values=0)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_logarithmic_space(self):
        for i in range(1, self.__number_inputs):
            size = randint(-self.__minimum_size, self.__maximum_size)
            minimum = randint(0, 5)
            maximum = randint(minimum, 5)
            generated = algorithm.logspace(minimum, maximum, size)
            reference = np.logspace(minimum, maximum, size)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_linear_space(self):
        for i in range(0, self.__number_inputs):
            size = randint(-self.__minimum_size, self.__maximum_size)
            minimum = randint(self.__minimum_size, self.__maximum_size / 1000)
            maximum = randint(minimum, self.__maximum_size)
            generated = algorithm.linspace(minimum, maximum, size)
            reference = np.linspace(minimum, maximum, size)
            np.testing.assert_array_almost_equal(generated, reference)
