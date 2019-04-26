import unittest
import pedsp.statistics as statistics
import numpy as np
import scipy.stats
import scipy.stats.mstats
from numpy import linalg as LA
from utility import generate_inputs


class TestStatisticsMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6

    # TODO: test median
    # TODO: implement this list https://www.programcreek.com/python/example/66766/scipy.stats.kurtosis

    def test_max(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.max(data)
            reference = max(data)
            self.assertAlmostEqual(generated, reference)

            generated = statistics.max_abs(data)
            reference = max(data, key=abs)
            self.assertAlmostEqual(generated, reference)

    def test_min(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.min(data)
            reference = min(data)
            self.assertAlmostEqual(generated, reference)

            generated = statistics.min_abs(data)
            reference = min(data, key=abs)
            self.assertAlmostEqual(generated, reference)

    def test_peak(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated, _ = statistics.peak(data)
            reference = np.argmax(data)
            self.assertAlmostEqual(generated, reference)

            generated, _ = statistics.peak_abs(data)
            reference = np.argmax(np.abs(data))
            self.assertAlmostEqual(generated, reference)

    def test_norm(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.norm(data)
            reference = LA.norm(data)
            self.assertAlmostEqual(generated, reference)

    def test_harmonic_mean(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.harmonic_mean(data)
            reference = scipy.stats.mstats.hmean(data)
            self.assertAlmostEqual(generated, reference)

    def test_generalized_mean(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.geometric_mean(data)
            reference = scipy.stats.mstats.gmean(data)
            self.assertAlmostEqual(generated, reference)

    def test_mean(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.mean(data)
            reference = np.mean(data)
            self.assertAlmostEqual(generated, reference.item())

    def test_variance(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.variance(data)
            reference = np.var(data)
            self.assertAlmostEqual(generated, reference.item())

    def test_std(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.standard_deviation(data)
            reference = np.std(data)
            self.assertAlmostEqual(generated, reference.item())

    def test_skewness(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.skewness(data)
            reference = scipy.stats.mstats.skew(data)
            self.assertAlmostEqual(generated, reference.item())

    def test_kurtosis(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.kurtosis(data)
            reference = scipy.stats.mstats.kurtosis(data, fisher=False)
            self.assertAlmostEqual(generated, reference.item())

    def test_moment(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            for i in range(2, 8):
                generated = statistics.moment(data, i)
                reference = scipy.stats.mstats.moment(data, i)
                self.assertAlmostEqual(generated, reference)
