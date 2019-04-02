import unittest
import random
import spectrum.tools as tools
import pedsp.converter as converter
import numpy as np
from utility import generate_inputs


class TestConverterMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6

    def test_deg2rad(self):
        for _ in range(self.__number_inputs):
            degree = random.uniform(0.0, 360.0)
            generated = converter.deg2rad(degree)
            reference = np.deg2rad(degree)
            self.assertAlmostEqual(generated, reference)

    def test_rad2deg(self):
        for _ in range(0, self.__number_inputs):
            degree = random.uniform(0.0, 2.0 * np.pi)
            generated = converter.rad2deg(degree)
            reference = np.rad2deg(degree)
            self.assertAlmostEqual(generated, reference)

    def test_pow2db(self):
        for _ in range(0, self.__number_inputs):
            degree = random.uniform(0.0, 20.0)
            generated = converter.pow2db(degree)
            reference = tools.pow2db(degree)
            self.assertAlmostEqual(generated, reference)

    def test_db2pow(self):
        for _ in range(self.__number_inputs):
            degree = random.uniform(0.0, 20.0)
            generated = converter.db2pow(degree)
            reference = tools.db2pow(degree)
            self.assertAlmostEqual(generated, reference)

    def test_mag2db(self):
        for _ in range(self.__number_inputs):
            degree = random.uniform(0.0, 20.0)
            generated = converter.mag2db(degree)
            reference = tools.mag2db(degree)
            self.assertAlmostEqual(generated, reference)

    def test_db2mag(self):
        for _ in range(self.__number_inputs):
            degree = random.uniform(0.0, 20.0)
            generated = converter.db2mag(degree)
            reference = tools.db2mag(degree)
            self.assertAlmostEqual(generated, reference)

    def test_peak2peak(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            data = 1000 * data
            generated = converter.peak2peak(data)
            reference = np.ptp(data).item()
            self.assertAlmostEqual(generated, reference)

    def test_peak2rms(self):
        for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            data = 1000 * data
            generated = converter.peak2rms(data)
            reference = np.amax(data) / np.sqrt(np.mean(data ** 2))
            self.assertAlmostEqual(generated, reference)

    def test_complex2real(self):
        for _ in range(self.__number_inputs):
            data = np.random.rand(random.randint(
                self.__minimum_size, self.__maximum_size), 2)
            data = data.view(dtype=np.complex128)
            data = data.reshape(data.shape[0],)
            real_generated, imag_generated = converter.complex2real(data)
            np.testing.assert_array_almost_equal(real_generated, np.real(data))
            np.testing.assert_array_almost_equal(imag_generated, np.imag(data))

    # def test_real2complex(self):
    #     for data in generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
    #         generated = converter.real2complex(data)
    #         reference = data.astype(np.complex128)
    #         np.testing.assert_array_almost_equal(generated, reference)
    #
    # def test_ri2complex(self):
    #     for i in range(0, self.__number_inputs):
    #         data = np.random.rand(random.randint(self.__minimum_size, self.__maximum_size), 2)
    #         data = data.view(dtype=np.complex128)
    #         data = data.reshape(data.shape[0],)
    #         generated = converter.ri2complex(np.real(data), np.imag(data))
    #         np.testing.assert_array_almost_equal(generated, data)
