import unittest
import pedsp.spectral as spectral
import numpy as np
import scipy.fftpack as fftpack
import scipy.signal as signal
from utility import generate_pair_inputs, generate_inputs


class TestSpectralMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6

    def test_convolution(self):
        first, second = generate_pair_inputs(
            self.__number_inputs, self.__minimum_size, self.__maximum_size)
        for l, r in zip(first, second):
            generated = spectral.conv(l, r)
            reference = np.convolve(l, r)
            np.testing.assert_array_almost_equal(
                generated, reference[:len(generated)])

    def test_correlation(self):
        first, second = generate_pair_inputs(
            self.__number_inputs, self.__minimum_size, self.__maximum_size)
        for l, r in zip(first, second):
            generated = spectral.xcorr(l, r)
            reference = np.correlate(l, r, "full")
            np.testing.assert_array_almost_equal(
                generated, reference[len(generated) - 1:])

    def test_hilbert(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            reference = spectral.hilbert(data)
            generated = signal.hilbert(data)
            np.testing.assert_array_almost_equal(reference, generated)

    def test_hartley(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            reference = spectral.hartley(data)
            temporal = spectral.rfft(data)
            generated = np.real(temporal) - np.imag(temporal)
            np.testing.assert_array_almost_equal(reference[:len(generated)], generated)

    def test_dct(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = spectral.dct(data)
            reference = fftpack.dct(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_idct(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            forward = spectral.dct(data)
            backward = spectral.idct(forward)
            np.testing.assert_array_almost_equal(data, backward)

    def test_real_fft(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = spectral.rfft(data)
            reference = np.fft.rfft(data)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_real_ifft(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            forward = spectral.rfft(data)
            generated = spectral.irfft(forward)
            reference = np.fft.irfft(forward)
            np.testing.assert_array_almost_equal(generated, reference)

    def test_real_complex_fft(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            complex_data = data.astype(np.complex128)
            forward = spectral.fft(complex_data)
            backward = spectral.ifft(forward)
            np.testing.assert_array_almost_equal(backward, complex_data)

    def test_periodogram(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            data = 10 * data
            generated = spectral.spectrum(data)
            reference = np.abs(np.fft.rfft(data)) ** 2
            np.testing.assert_array_almost_equal(generated, reference, 3)
