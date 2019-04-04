import unittest
import random
import madmom.audio.filters as maf
import pedsp.auditory as auditory
import pedsp.algorithm as algorithm
import pydrobert.speech.scales as scales

class TestAuditoryMethods(unittest.TestCase):

    __number_inputs = 10000
    __maximum_size = 1 << 14
    __minimum_size = 1 << 6
    __minimum_frequency = 10
    __maximum_frequency = 8000

    def test_hz2mel(self):
        for _ in range(self.__number_inputs):
            f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            generated = auditory.hertz2mel(f)
            reference = maf.hz2mel(f)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.mel2hertz(generated)
            self.assertAlmostEqual(f, restored)

    def test_hz2bark(self):
        scale = scales.BarkScaling()
        for _ in range(self.__number_inputs):
            f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            generated = auditory.hertz2bark(f)
            reference = scale.hertz_to_scale(f)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.bark2hertz(generated)
            self.assertAlmostEqual(f, restored)

    def test_hz2erb(self):
        for _ in range(self.__number_inputs):
            f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            generated = auditory.hertz2erb(f)
            reference = maf.hz2erb(f)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.erb2hertz(generated)
            self.assertAlmostEqual(f, restored)

    def test_mel2hertz(self):
        for _ in range(self.__number_inputs):
            mel = random.uniform(maf.hz2mel(self.__minimum_frequency), maf.hz2mel(self.__maximum_frequency))
            generated = auditory.mel2hertz(mel)
            reference = maf.mel2hz(mel)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.hertz2mel(generated)
            self.assertAlmostEqual(mel, restored)

    def test_bark2hertz(self):
        scale = scales.BarkScaling()
        for _ in range(self.__number_inputs):
            bark = random.uniform(scale.scale_to_hertz(self.__minimum_frequency), scale.scale_to_hertz(self.__maximum_frequency))
            generated = auditory.bark2hertz(bark)
            reference = scale.scale_to_hertz(bark)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.hertz2bark(generated)
            self.assertAlmostEqual(bark, restored)

    def test_erb2hertz(self):
        for _ in range(self.__number_inputs):
            erb = random.uniform(maf.hz2erb(self.__minimum_frequency), maf.hz2erb(self.__maximum_frequency))
            generated = auditory.erb2hertz(erb)
            reference = maf.erb2hz(erb)
            self.assertAlmostEqual(generated, reference)

            restored = auditory.hertz2erb(generated)
            self.assertAlmostEqual(erb, restored)

    def test_barkspace(self):
        for _ in range(100):
            min_f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            max_f = random.uniform(min_f, self.__maximum_frequency)
            n = random.randint(0, self.__maximum_size)
            frequencies = algorithm.linspace(min_f, max_f, n)
            generated = auditory.barkspace(min_f, max_f, n)
            for f, bark in zip(frequencies, generated):
                self.assertAlmostEqual(auditory.hertz2bark(f), bark)

    def test_centspace(self):
        for _ in range(100):
            min_f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            max_f = random.uniform(min_f, self.__maximum_frequency)
            n = random.randint(0, self.__maximum_size)
            frequencies = algorithm.linspace(min_f, max_f, n)
            generated = auditory.centspace(min_f, max_f, n)
            for f, bark in zip(frequencies, generated):
                self.assertAlmostEqual(auditory.hertz2cent(f), bark)

    def test_erbspace(self):
        for _ in range(100):
            min_f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            max_f = random.uniform(min_f, self.__maximum_frequency)
            n = random.randint(0, self.__maximum_size)
            frequencies = algorithm.linspace(min_f, max_f, n)
            generated = auditory.erbspace(min_f, max_f, n)
            for f, bark in zip(frequencies, generated):
                self.assertAlmostEqual(auditory.hertz2erb(f), bark)

    def test_melspace(self):
        for _ in range(100):
            min_f = random.uniform(self.__minimum_frequency, self.__maximum_frequency)
            max_f = random.uniform(min_f, self.__maximum_frequency)
            n = random.randint(0, self.__maximum_size)
            frequencies = algorithm.linspace(min_f, max_f, n)
            generated = auditory.melspace(min_f, max_f, n)
            for f, bark in zip(frequencies, generated):
                self.assertAlmostEqual(auditory.hertz2mel(f), bark)
