import unittest
import pedsp.algorithm as algorithm
import numpy as np
from random import randint


class TestAlgorithmMethods(unittest.TestCase):

    __iterations = 10
    __minimum = 0
    __maximum = 1000

    def test_scale(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            factor = randint(0, 5)
            generated = algorithm.scale(data, factor)
            reference = data * factor
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_scale_clip(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            factor = randint(0, 5)
            min = randint(self.__minimum, self.__maximum)
            max = randint(min, self.__maximum)
            generated = algorithm.scale_clip(data, factor, min, max)
            reference = np.clip(data * factor, min, max)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_clip(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            min = randint(self.__minimum, self.__maximum)
            max = randint(min, self.__maximum)
            generated = algorithm.clip(data,  min, max)
            reference = np.clip(data, min, max)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_round(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            generated = algorithm.round(data)
            reference = np.round(data)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_floor(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            generated = algorithm.floor(data)
            reference = np.floor(data)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_trunc(self):
        for i in range(0, self.__iterations):
            size = randint(self.__minimum, self.__maximum)
            data = np.random.uniform(low=1, high=20, size=(size,))
            generated = algorithm.trunc(data)
            reference = np.trunc(data)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_abs(self):
        for i in range(0, self.__iterations):
            size = randint(-self.__minimum, self.__maximum)
            data = np.random.uniform(low=-20, high=20, size=(size,))
            generated = algorithm.abs(data)
            reference = np.abs(data)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_normalize(self):
        for i in range(0, self.__iterations):
            size = randint(-self.__minimum, self.__maximum)
            data = np.random.uniform(low=-20, high=20, size=(size,))
            generated = algorithm.normalize(data)
            reference = data / np.max(np.abs(data)).item()
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_logspace(self):
        for i in range(1, self.__iterations):
            size = randint(-self.__minimum, self.__maximum)
            min = randint(0, 5)
            max = randint(min, 5)
            generated = algorithm.logspace(min, max, size)
            reference = np.logspace(min, max, size)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_linspace(self):
        for i in range(0, self.__iterations):
            size = randint(-self.__minimum, self.__maximum)
            min = randint(self.__minimum, self.__maximum / 1000)
            max = randint(min, self.__maximum)
            generated = algorithm.linspace(min, max, size)
            reference = np.linspace(min, max, size)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)