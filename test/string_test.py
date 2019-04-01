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
        for i in range(0, self.__number_inputs):
            data = []
            for i in range(0, 10):
                data.append(self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)))

            delimiter = random.choice(string.ascii_letters)
            generated = pedsp.string.join(data, delimiter)
            reference = delimiter.join([str(x) for x in data])
            self.assertEqual(generated, reference)

    def test_split(self):
        for i in range(0, self.__number_inputs):
            str = ""
            delimiter = random.choice(string.ascii_letters)
            for i in range(0, 10):
                str = str + delimiter + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))

            generated = pedsp.string.split(str, delimiter)
            reference = list(filter(None, str.split(delimiter)))
            self.assertEqual(generated, reference)

    def test_to_lower(self):
        for i in range(0, self.__number_inputs):
            str = self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))
            generated = pedsp.string.to_lower(str)
            reference = str.lower()
            self.assertEqual(generated, reference)

    def test_to_upper(self):
        for i in range(0, self.__number_inputs):
            str = self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size))
            generated = pedsp.string.to_upper(str)
            reference = str.upper()
            self.assertEqual(generated, reference)

    def test_trim(self):
        for i in range(0, self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            str = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.trim(str)
            reference = str.strip()
            self.assertEqual(generated, reference)

    def test_rtrim(self):
        for i in range(0, self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            str = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.rtrim(str)
            reference = str.rstrip()
            self.assertEqual(generated, reference)

    def test_ltrim(self):
        for i in range(0, self.__number_inputs):
            left_trim = " " * random.randint(0, 10)
            right_trim = " " * random.randint(0, 10)
            str = left_trim + self.__generate_string(random.randint(self.__minimum_size, self.__maximum_size)) + right_trim
            generated = pedsp.string.ltrim(str)
            reference = str.lstrip()
            self.assertEqual(generated, reference)