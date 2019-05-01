from unittest import TestLoader, TextTestRunner, TestSuite
from windowing_test import TestWindowingMethods
from statistics_test import TestStatisticsMethods
from algorithm_test import TestAlgorithmMethods
from spectral_test import TestSpectralMethods
from converter_test import TestConverterMethods
from core_test import TestCoreMethods
from string_test import TestStringMethods
from oscillator_test import TestOscillatorMethods
from auditory_test import TestAuditoryMethods
from temporal_features_test import TestTemporalFeatureMethods
from statistical_features_test import TestStatisticalFeatureMethods
from spectral_features_test import TestSpectralFeatureMethods
from filter_test import TestFilterMethods
from io_test import TestIOMethods


if __name__ == "__main__":

    loader = TestLoader()
    tests = [
        loader.loadTestsFromTestCase(test)
        for test in (TestWindowingMethods, TestCoreMethods, TestConverterMethods,
                     TestStatisticsMethods, TestAlgorithmMethods, TestSpectralMethods,
                     TestStringMethods, TestOscillatorMethods, TestAuditoryMethods,
                     TestTemporalFeatureMethods, TestStatisticalFeatureMethods, TestSpectralFeatureMethods,
                     TestFilterMethods, TestIOMethods)
    ]
    suite = TestSuite(tests)

    runner = TextTestRunner(verbosity=2)
    result = runner.run(suite)
    exit(0 if result.wasSuccessful() else -1)
