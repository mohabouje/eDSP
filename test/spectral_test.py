import unittest
import pedsp.spectral as spectral
import numpy as np
import scipy.signal as signal
from random import randint



class TestSpectralMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6
    __functions = [np.hanning, np.hanning, signal]


    def generate_inputs(self):
        left = []
        right = []
        for i in range(0, self.__number_inputs):
            size = randint(self.__minimum_size, self.__maximum_size)
            left.append(np.hamming(size))
            right.append(np.hanning(size))
        return left, right


    def test_conv(self):
        left, right = self.generate_inputs()
        for l, r in zip(left, right):
            generated = spectral.conv(l, r)
            reference = np.convolve(l, r)
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)

    def test_xcorr(self):
        left, right = self.generate_inputs()
        for l, r in zip(left, right):
            generated = spectral.xcorr(l, r)
            reference = np.correlate(l, r, "full")[len(l) - 1:]
            for g, r in zip(generated, reference):
                self.assertAlmostEqual(g, r)