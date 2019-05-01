import unittest
import random
import pedsp.filter as flt
import numpy as np

class TestFilterMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6

    @staticmethod
    def __running_mean(x, N):
        cumsum = np.cumsum(np.insert(x, 0, 0))
        return (cumsum[N:] - cumsum[:-N]) / float(N)

    def test_median_filter_methods(self):
        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f = flt.MovingMedianFilter(kernel)
        self.assertEqual(f.size(), kernel)

        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f.resize(kernel)
        self.assertEqual(f.size(), kernel)

    def test_average_filter_methods(self):
        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f = flt.MovingAverageFilter(kernel)
        self.assertEqual(f.size(), kernel)

        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f.resize(kernel)
        self.assertEqual(f.size(), kernel)

    def test_rms_filter_methods(self):
        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f = flt.MovingRmsFilter(kernel)
        self.assertEqual(f.size(), kernel)

        kernel = random.randint(self.__minimum_size, self.__maximum_size)
        f.resize(kernel)
        self.assertEqual(f.size(), kernel)

    # def test_average_filter(self):
    #     for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
    #         kernel = random.randint(0, len(data))
    #         f = flt.MovingAverageFilter(kernel)
    #         generated = f.filter(data)
    #         reference = self.__running_mean(data, kernel)
    #         np.testing.assert_array_almost_equal(generated, reference)
