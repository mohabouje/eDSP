import unittest
import pedsp.windowing as windowing
import numpy as np
import scipy.signal as signal
import scipy.signal.windows as spw
from random import randint


class TestWindowingMethods(unittest.TestCase):

    # TODO: implement test for the welch-window

    def test_hamming(self):
        size = randint(0, 1000)
        generated = windowing.hamming(size)
        reference = np.hamming(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_hanning(self):
        size = randint(0, 1000)
        generated = windowing.hanning(size)
        reference = np.hanning(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_bartlett(self):
        size = randint(0, 1000)
        generated = windowing.bartlett(size)
        reference = np.bartlett(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_blackman(self):
        size = randint(0, 1000)
        generated = windowing.blackman(size)
        reference = np.blackman(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_blackman_harris(self):
        size = randint(0, 1000)
        generated = windowing.blackman_harris(size)
        reference = signal.blackmanharris(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_triangular(self):
        size = randint(0, 1000)
        generated = windowing.triangular(size)
        reference = spw.triang(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_blackman_nuttall(self):
        size = randint(0, 1000)
        generated = windowing.blackman_nutall(size)
        reference = signal.nuttall(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    def test_boxcar(self):
        size = randint(0, 1000)
        generated = windowing.boxcar(size)
        reference = signal.boxcar(size)
        for g, r in zip(generated, reference):
            self.assertAlmostEqual(g, r)

    # # Warning: The returns value of the flat-top window differ depending of the version of scipy
    # def test_flattop(self):
    #     size = randint(0, 1000)
    #     generated = windowing.flattop(size)
    #     reference = signal.flattop(size)
    #     for g, r in zip(generated, reference):
    #         self.assertAlmostEqual(g, r)

    # # Warning: The returns value of the flat-top window differ depending of the version of scipy
    # def test_rectangular(self):
    #     size = randint(0, 1000)
    #     generated = windowing.rectangular(size)
    #     reference = np.ones(shape=(size,))
    #     for g, r in zip(generated, reference):
    #         self.assertAlmostEqual(g, r)
