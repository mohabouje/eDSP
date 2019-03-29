import unittest
import pedsp.statistics as statistics
import numpy as np
import scipy.stats
import scipy.stats.mstats
from random import randint


class TestStatisticsMethods(unittest.TestCase):

    # TODO: test entropy
    # TODO: test median
    # TODO: implement this list https://www.programcreek.com/python/example/66766/scipy.stats.kurtosis

    def test_hmean(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.harmonic_mean(data)
        reference = scipy.stats.mstats.hmean(data)
        self.assertAlmostEqual(generated, reference)

    def test_gmean(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=1, size=(size,))
        generated = statistics.geometric_mean(data)
        reference = scipy.stats.mstats.gmean(data)
        self.assertAlmostEqual(generated, reference)

    def test_mean(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.mean(data)
        reference = np.mean(data)
        self.assertAlmostEqual(generated, reference.item())

    def test_variance(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.variance(data)
        reference = np.var(data)
        self.assertAlmostEqual(generated, reference.item())

    def test_std(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.standard_deviation(data)
        reference = np.std(data)
        self.assertAlmostEqual(generated, reference.item())

    def test_skewness(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.skewness(data)
        reference = scipy.stats.mstats.skew(data)
        self.assertAlmostEqual(generated, reference.item())

    def test_kurtosis(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        generated = statistics.kurtosis(data)
        reference = scipy.stats.mstats.kurtosis(data, fisher=False)
        self.assertAlmostEqual(generated, reference.item())

    def test_moment(self):
        size = randint(0, 1000)
        data = np.random.uniform(low=0.5, high=20, size=(size,))
        for i in range(2, 8):
            generated = statistics.moment(data, i)
            reference = scipy.stats.mstats.moment(data, i)
            self.assertAlmostEqual(generated, reference)

