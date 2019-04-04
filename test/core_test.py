import unittest
import datetime
import random
import pedsp.core as core
from dateutil.parser import parse
from pkg_resources import parse_version


class TestCoreMethods(unittest.TestCase):

    @staticmethod
    def __random_string():
        s = 'ABCDEFGHIJKLMNOPQRSTUVWXYZ'
        return ''.join([random.choice(s) for _ in range(16)])

    def test_build_time(self):
        build_time = core.get_build_time()
        parsed = parse(build_time)
        self.assertTrue(parsed < datetime.datetime.now())

    def test_build_date(self):
        build_time = core.get_build_date()
        parsed = parse(build_time)
        self.assertTrue(parsed < datetime.datetime.now())

    def test_version(self):
        serialized = core.get_version()
        self.assertTrue(parse_version(serialized))
        split = serialized.split(".")
        self.assertEqual(int(split[0]), core.get_major_version())
        self.assertEqual(int(split[1]), core.get_minor_version())
        self.assertEqual(int(split[2]), core.get_patch_version())

    def test_default_libraries(self):
        self.assertEqual(core.get_fft_library(), "fftw")
        self.assertEqual(core.get_codec_library(), "sndfile")
        self.assertEqual(core.get_resample_library(), "samplerate")

    def test_set_environment(self):
        for _ in range(0, random.randint(0, 1000)):
            tag = self.__random_string()
            data = self.__random_string()
            error = core.set_environment(tag, data)
            self.assertEqual(error, 0)
            self.assertTrue(core.exist_environment(tag))

    def test_get_environment(self):
        for _ in range(0, random.randint(0, 1000)):
            tag = self.__random_string()
            data = self.__random_string()
            error = core.set_environment(tag, data)
            self.assertEqual(error, 0)

            recovered, error = core.get_environment(tag)
            self.assertEqual(error, 0)
            self.assertEqual(data, recovered)
            self.assertTrue(core.exist_environment(tag))
