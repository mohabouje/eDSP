import unittest
import random
import pedsp.oscillator as oscillator
import numpy as np
import scipy.signal as sp
from utility import generate_timestamps

class TestOscillatorMethods(unittest.TestCase):

    __number_iterations = 10
    __minimum_frequency = 1
    __maximum_frequency = int(1e6)
    __maximum_amplitude = 100.0
    __maximum_samples = 1000000

    def test_oscillator_constructor(self):
        for _ in range(self.__number_iterations):
            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            phase = random.uniform(0, 2 * np.pi)
            frequency = random.randint(
                self.__minimum_frequency, self.__maximum_frequency / 2)
            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            sinusoidal = oscillator.Sinusoidal(amp=amplitude, sr=sr, f=frequency, p=phase)
            self.assertEqual(sr, sinusoidal.sample_rate())
            self.assertEqual(amplitude, sinusoidal.amplitude())
            self.assertEqual(frequency, sinusoidal.frequency())
            self.assertEqual(phase, sinusoidal.phase())

    def test_oscillator_setter_and_getter(self):
        for _ in range(self.__number_iterations):
            sinusoidal = oscillator.Sinusoidal(amp=0, sr=0, f=0, p=0)

            timestamp = random.uniform(0.0, 10.0)
            sinusoidal.set_timestamp(timestamp)
            self.assertEqual(timestamp, sinusoidal.timestamp())

            frequency = random.randint(
                self.__minimum_frequency, self.__maximum_frequency / 2)
            sinusoidal.set_frequency(frequency)
            self.assertEqual(frequency, sinusoidal.frequency())

            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            sinusoidal.set_amplitude(amplitude)
            self.assertEqual(amplitude, sinusoidal.amplitude())

            phase = random.uniform(0, 2 * np.pi)
            sinusoidal.set_phase(phase)
            self.assertEqual(phase, sinusoidal.phase())

            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            sinusoidal.set_sample_rate(sr)
            self.assertEqual(sr, sinusoidal.sample_rate())

    def test_reset(self):
        for _ in range(self.__number_iterations):
            sinusoidal = oscillator.Sinusoidal(amp=0, sr=0, f=0, p=0)
            timestamp = random.uniform(0.0, 10.0)
            sinusoidal.set_timestamp(timestamp)

            sinusoidal.reset()
            self.assertEqual(0, sinusoidal.timestamp())

    def test_sinusoidal_generate_data(self):
        for _ in range(self.__number_iterations):
            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            phase = random.uniform(0, 2 * np.pi)
            frequency = random.randint(self.__minimum_frequency, self.__maximum_frequency / 2)
            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            n = int(random.uniform(1.0, 3.0) * sr)
            init_t = random.uniform(0.0, 10.0)

            # Generate data from numpy
            samples = generate_timestamps(init_t, n, sr)
            reference = amplitude * np.sin(2 * np.pi * frequency * samples + phase)

            sinusoidal = oscillator.Sinusoidal(amp=amplitude, sr=sr, f=frequency, p=phase)
            sinusoidal.set_timestamp(init_t)
            generated = sinusoidal.generate(n)

            self.assertEqual(len(generated), n)
            self.assertAlmostEqual(
                samples[n - 1] + 1.0 / sr, sinusoidal.timestamp())
            np.testing.assert_array_almost_equal(generated, reference)

    def test_square_generate_data(self):
        for _ in range(self.__number_iterations):
            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            frequency = random.randint(self.__minimum_frequency, self.__maximum_frequency / 2)
            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            duty = random.uniform(0.0, 1.0)
            n = int(random.uniform(1.0, 3.0) * sr)
            init_t = random.uniform(0.0, 10.0)

            # Generate data from numpy
            samples = generate_timestamps(init_t, n, sr)
            reference = amplitude * sp.square(2 * np.pi * frequency * samples, duty=duty)

            square = oscillator.Square(amp=amplitude, sr=sr, f=frequency, duty=duty)
            square.set_timestamp(init_t)
            generated = square.generate(n)

            self.assertEqual(len(generated), n)
            self.assertAlmostEqual(samples[n - 1] + 1.0 / sr, square.timestamp())
            np.testing.assert_array_almost_equal(
                np.abs(generated), np.abs(reference))

    def test_sawtooth_generate_data(self):
        for _ in range(self.__number_iterations):
            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            frequency = random.randint(
                self.__minimum_frequency, self.__maximum_frequency / 2)
            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            width = random.uniform(0.0, 1.0)
            n = int(random.uniform(1.0, 3.0) * sr)
            init_t = random.uniform(0.0, 10.0)

            # Generate data from numpy
            samples = generate_timestamps(init_t, n, sr)
            reference = amplitude * sp.sawtooth(2 * np.pi * frequency * samples, width=width)

            sawtooth = oscillator.Sawtooth(amp=amplitude, sr=sr, f=frequency, width=width)
            sawtooth.set_timestamp(init_t)
            generated = sawtooth.generate(n)

            self.assertEqual(len(generated), n)
            self.assertAlmostEqual(samples[n - 1] + 1.0 / sr, sawtooth.timestamp())
            np.testing.assert_array_almost_equal(generated, reference, 4)

    def test_triangular_generate_data(self):
        for _ in range(self.__number_iterations):
            amplitude = random.uniform(1.0, self.__maximum_amplitude)
            frequency = random.randint(
                self.__minimum_frequency, self.__maximum_frequency / 2)
            sr = random.uniform(2 * frequency, self.__maximum_frequency)
            n = int(random.uniform(1.0, 3.0) * sr)
            init_t = random.uniform(0.0, 10.0)

            # Generate data from numpy
            samples = generate_timestamps(init_t, n, sr)
            reference = amplitude * sp.sawtooth(2 * np.pi * frequency * samples, width=0.5)

            sawtooth = oscillator.Triangular(amp=amplitude, sr=sr, f=frequency)
            sawtooth.set_timestamp(init_t)
            generated = sawtooth.generate(n)

            self.assertEqual(len(generated), n)
            self.assertAlmostEqual(samples[n - 1] + 1.0 / sr, sawtooth.timestamp())
            np.testing.assert_array_almost_equal(generated, reference)
