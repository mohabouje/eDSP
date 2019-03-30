from unittest import TestLoader, TextTestRunner, TestSuite
from windowing_test import TestWindowingMethods
from statistics_test import TestStatisticsMethods
from algorithm_test import TestAlgorithmMethods
from spectral_test import TestSpectralMethods

if __name__ == "__main__":

    loader = TestLoader()
    tests = [
        loader.loadTestsFromTestCase(test)
        for test in (TestWindowingMethods, TestStatisticsMethods, TestAlgorithmMethods, TestSpectralMethods)
    ]
    suite = TestSuite(tests)

    runner = TextTestRunner(verbosity=2)
    runner.run(suite)
