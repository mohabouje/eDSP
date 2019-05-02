import unittest
import random
import scipy
import scipy.signal
import scipy.stats
import scipy.stats.mstats
import utility
import pedsp.spectral as spectral
import numpy as np
import pyAudioAnalysis.audioFeatureExtraction as extractor

class TestSpectralFeatureMethods(unittest.TestCase):

    __number_inputs = []
    __maximum_size = []
    __minimum_size = []
    __database = []

    def __init__(self, *args, **kwargs):
        self.__number_inputs = 1
        self.__maximum_size = 10000
        self.__minimum_size = 100
        self.__database = utility.read_audio_test_files(self.__number_inputs, self.__minimum_size, self.__maximum_size)
        super(TestSpectralFeatureMethods, self).__init__(*args, **kwargs)

    @staticmethod
    def __compute_flatness(data):
        geometricMean = scipy.stats.mstats.gmean(data)
        arithmeticMean = data.mean()
        return geometricMean / arithmeticMean

    @staticmethod
    def __compute_crest(data):
        absData = abs(data)
        return absData[np.argmax(absData)] / np.sum(absData)

    @staticmethod
    def __spectral_entropy(psd):
        psd_norm = np.divide(psd, psd.sum())
        se = -np.multiply(psd_norm, np.log2(psd_norm)).sum()
        se /= np.log2(psd_norm.size)
        return se

    def test_spectral_centroid(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            ind = (np.arange(1, len(data) + 1)) * (fs/(2.0 * len(data)))
            generated = spectral.spectral_centroid(data, ind)
            centroid, _ = extractor.stSpectralCentroidAndSpread(data, fs)
            reference = centroid * (fs / 2.0)  # de-normalize
            error = utility.get_change(generated, reference)
            self.assertTrue(error < 1)

    def test_spectral_spread(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            ind = (np.arange(1, len(data) + 1)) * (fs/(2.0 * len(data)))
            generated = spectral.spectral_spread(data, ind)
            _, spread = extractor.stSpectralCentroidAndSpread(data, fs)
            reference = spread * (fs / 2.0)  # de-normalize
            self.assertAlmostEqual(generated, reference, 4)

    def test_spectral_flux(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_flux(data, data)
            reference = extractor.stSpectralFlux(data, data)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_rolloff(self):
        for fs, data in self.__database:
            percentage = random.uniform(0.0, 1.0)
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_rolloff(data, percentage)
            reference = extractor.stSpectralRollOff(data, percentage, fs)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_flatness(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_flatness(data)
            reference = self.__compute_flatness(data)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_crest(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_crest(data)
            reference = self.__compute_crest(data)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_kurtosis(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_kurtosis(data)
            reference = scipy.stats.mstats.kurtosis(data, fisher=False)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_skewness(self):
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_skewness(data)
            reference = scipy.stats.mstats.skew(data)
            self.assertAlmostEqual(generated, reference.item(), 5)

    def test_spectral_entropy(self):
        import math
        for fs, data in self.__database:
            _, data = scipy.signal.periodogram(data, fs)
            data = (data + utility.epsilon) * 100
            generated = spectral.spectral_entropy(data)
            reference = self.__spectral_entropy(data)
            self.assertAlmostEqual(generated, reference.item(), 5)
