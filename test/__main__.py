from unittest import TestLoader, TextTestRunner, TestSuite
from windowing_test import TestWindowingMethods
from statistics_test import TestStatisticsMethods
from algorithm_test import TestAlgorithmMethods
from spectral_test import TestSpectralMethods
from converter_test import TestConverterMethods
from core_test import TestCoreMethods

from sys import exit

if __name__ == "__main__":

    loader = TestLoader()
    tests = [
        loader.loadTestsFromTestCase(test)
        for test in (TestWindowingMethods, TestCoreMethods, TestConverterMethods, TestStatisticsMethods, TestAlgorithmMethods, TestSpectralMethods)
    ]
    suite = TestSuite(tests)

    runner = TextTestRunner(verbosity=2)
    result = runner.run(suite)
    exit(0 if result.wasSuccessful() else -1)
