from unittest import TestLoader, TextTestRunner, TestSuite
from windowing_test import TestWindowingMethods
from statistics_test import TestStatisticsMethods
from algorithm_test import TestAlgorithmMethods

if __name__ == "__main__":

    loader = TestLoader()
    tests = [
        loader.loadTestsFromTestCase(test)
        for test in (TestWindowingMethods, TestStatisticsMethods, TestAlgorithmMethods)
    ]
    suite = TestSuite(tests)

    runner = TextTestRunner(verbosity=2)
    runner.run(suite)
