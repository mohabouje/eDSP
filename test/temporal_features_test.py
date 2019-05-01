import unittest
import random
import essentia.standard
import pedsp.temporal as temporal
import numpy as np
import utility
import pyAudioAnalysis.audioFeatureExtraction as extractor

class TestTemporalFeatureMethods(unittest.TestCase):

    __number_inputs = []
    __maximum_size = []
    __minimum_size = []
    __database = []

    def __init__(self, *args, **kwargs):
        self.__number_inputs = 10
        self.__maximum_size = 10000
        self.__minimum_size = 100
        self.__database = utility.read_audio_test_files(self.__number_inputs, self.__minimum_size, self.__maximum_size)
        super(TestTemporalFeatureMethods, self).__init__(*args, **kwargs)

    def test_rms(self):
        for _, data in self.__database:
            data = np.iinfo(np.uint8).max * data
            algo = essentia.standard.RMS()
            generated = temporal.rms(data)
            reference = algo.compute(data.astype(np.float32))
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    def test_duration(self):
        for fs, data in self.__database:
            algo = essentia.standard.Duration(sampleRate=fs)
            generated = temporal.duration(data, fs)
            reference = algo.compute(data.astype(np.float32))
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    def test_effective_duration(self):
        for fs, data in self.__database:
            threshold = random.uniform(0.0, 1.0)
            algo = essentia.standard.EffectiveDuration(sampleRate=fs, thresholdRatio=threshold)
            generated = temporal.effective_duration(data, fs, threshold)
            reference = algo.compute(data.astype(np.float32))
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    def test_energy(self):
        for _, data in self.__database:
            generated = temporal.energy(data)
            reference = len(data) * extractor.stEnergy(data)
            self.assertAlmostEqual(generated, reference)

    def test_power(self):
        for _, data in self.__database:
            generated = temporal.power(data)
            reference = extractor.stEnergy(data)
            self.assertAlmostEqual(generated, reference)

    def test_azcr(self):
        for _, data in self.__database:
            generated = temporal.azcr(data)
            reference = extractor.stZCR(data)
            self.assertAlmostEqual(generated, reference, 3)

    def test_leq(self):
        for _, data in self.__database:
            algo = essentia.standard.Leq()
            generated = temporal.leq(data)
            reference = algo.compute(data.astype(np.float32))
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    def test_rssq(self):
        for _, data in self.__database:
            generated = temporal.rssq(data)
            reference = np.sqrt(np.sum(data ** 2))
            self.assertAlmostEqual(generated, reference)
