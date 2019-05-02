import unittest
import pedsp.windowing as windowing
import numpy as np
import scipy.signal as signal
from random import randint


class TestWindowingMethods(unittest.TestCase):
    def test_hamming(self):
        size = randint(0, 1000)
        generated = windowing.hamming(size)
        reference = np.hamming(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_hanning(self):
        size = randint(0, 1000)
        generated = windowing.hanning(size)
        reference = np.hanning(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_bartlett(self):
        size = randint(0, 1000)
        generated = windowing.bartlett(size)
        reference = np.bartlett(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_blackman(self):
        size = randint(0, 1000)
        generated = windowing.blackman(size)
        reference = np.blackman(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_blackman_harris(self):
        size = randint(0, 1000)
        generated = windowing.blackman_harris(size)
        reference = signal.blackmanharris(size)
        np.testing.assert_array_almost_equal(reference, generated)

    # def test_triangular(self):
    #     size = randint(0, 1000)
    #     generated = windowing.triangular(size)
    #     reference = signal.triang(size)
    #     np.testing.assert_array_almost_equal(reference, generated)

    def test_blackman_nuttall(self):
        size = randint(0, 1000)
        generated = windowing.blackman_nutall(size)
        reference = signal.nuttall(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_boxcar(self):
        size = randint(0, 1000)
        generated = windowing.boxcar(size)
        reference = signal.boxcar(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_flattop(self):
        size = randint(0, 1000)
        generated = windowing.flattop(size)
        reference = signal.flattop(size)
        np.testing.assert_array_almost_equal(reference, generated)

    def test_rectangular(self):
        size = randint(0, 1000)
        generated = windowing.rectangular(size)
        reference = np.ones(shape=(size,))
        np.testing.assert_array_almost_equal(reference, generated)
