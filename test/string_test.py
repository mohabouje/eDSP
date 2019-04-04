import unittest
import random
import string
import pedsp.string


class TestStringMethods(unittest.TestCase):

    __number_inputs = 10
    __maximum_size = 20
    __minimum_size = 5

    @staticmethod
    def __generate_string(N):
        return ''.join(random.choice(string.ascii_letters + string.digits) for _ in range(N))

    def test_join(self):
        for _ in range(self.__number_inputs):
            data = []
            for _ in range(10):
                data.append(self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)))

            delimiter = random.choice(string.ascii_letters)
            generated = pedsp.string.join(data, delimiter)
            reference = delimiter.join([str(x) for x in data])
            self.assertEqual(generated, reference)

    def test_split(self):
        for _ in range(self.__number_inputs):
            s = ""
            delimiter = random.choice(string.ascii_letters)
            for _ in range(10):
                s = s + delimiter + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))

            generated = pedsp.string.split(s, delimiter)
            reference = list(filter(None, s.split(delimiter)))
            self.assertEqual(generated, reference)

    def test_to_lower(self):
        for _ in range(self.__number_inputs):
            s = self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))
            generated = pedsp.string.to_lower(s)
            reference = s.lower()
            self.assertEqual(generated, reference)

    def test_to_upper(self):
        for _ in range(self.__number_inputs):
            s = self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))
            generated = pedsp.string.to_upper(s)
            reference = s.upper()
            self.assertEqual(generated, reference)

    def test_trim(self):
        for _ in range(self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            s = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.trim(s)
            reference = s.strip()
            self.assertEqual(generated, reference)

    def test_rtrim(self):
        for _ in range(self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            s = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.rtrim(s)
            reference = s.rstrip()
            self.assertEqual(generated, reference)

    def test_ltrim(self):
        for _ in range(self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            s = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.ltrim(s)
            reference = s.lstrip()
            self.assertEqual(generated, reference)
