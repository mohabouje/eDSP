import unittest
import random
import scipy
import scipy.signal
import utility
import pedsp.statistics as statistics
import numpy as np
import scipy.ndimage.measurements as measure
import pyAudioAnalysis.audioFeatureExtraction as extractor

class TestStatisticalFeatureMethods(unittest.TestCase):

    __number_inputs = []
    __maximum_size = []
    __minimum_size = []
    __database = []

    def __init__(self, *args, **kwargs):
        self.__number_inputs = 1
        self.__maximum_size = 10000
        self.__minimum_size = 100
        self.__database = utility.read_audio_test_files(self.__number_inputs, self.__minimum_size, self.__maximum_size)
        super(TestStatisticalFeatureMethods, self).__init__(*args, **kwargs)

    def test_centroid(self):
        for fs, data in self.__database:
            generated = statistics.centroid(data)
            reference = measure.center_of_mass(data)
            self.assertAlmostEqual(generated, reference[0])

    def test_weighted_centroid(self):
        for fs, data in self.__database:
            ind = (np.arange(1, len(data) + 1)) * (fs/(2.0 * len(data)))
            generated = statistics.weighted_centroid(data, ind)
            centroid, _ = extractor.stSpectralCentroidAndSpread(data, fs)
            reference = centroid * (fs / 2.0)  # de-normalize
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    # def test_weighted_spread(self):
    #     for fs, data in self.__database:
    #         ind = (np.arange(1, len(data) + 1)) * (fs/(2.0 * len(data)))
    #         generated = statistics.weighted_spread(data, ind)
    #         _, spread = extractor.stSpectralCentroidAndSpread(data, fs)
    #         reference = spread * (fs / 2.0)  # de-normalize
    #         error = utility.get_change(generated, reference)
    #         self.assertTrue(error < 1)

    def test_flux(self):
        for fs, data in self.__database:
            generated = statistics.flux(data, data)
            reference = extractor.stSpectralFlux(data, data)
            self.assertAlmostEqual(generated, reference)

    def test_rolloff(self):
        for fs, data in self.__database:
            percentage = random.uniform(0.0, 1.0)
            generated = statistics.rolloff(data, percentage)
            reference = extractor.stSpectralRollOff(data, percentage, fs)
            self.assertAlmostEqual(generated, reference)

    @staticmethod
    def __compute_flatness(data):
        geometricMean = scipy.stats.mstats.gmean(data)
        arithmeticMean = data.mean()
        return geometricMean / arithmeticMean

    @staticmethod
    def __compute_crest(data):
        absData = abs(data)
        return absData[np.argmax(absData)] / np.sum(absData)

    def test_flatness(self):
        for data in utility.generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.flatness(data)
            reference = self.__compute_flatness(data)
            self.assertAlmostEqual(generated, reference)

    def test_crest(self):
        for data in utility.generate_inputs(self.__number_inputs, self.__minimum_size, self.__maximum_size):
            generated = statistics.crest(data)
            reference = self.__compute_crest(data)
            self.assertAlmostEqual(generated, reference)
