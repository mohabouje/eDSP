import unittest
import pedsp.io as io
import numpy as np
import utility
import random
import taglib
import os.path

class TestIOMethods(unittest.TestCase):

    def testing_metadata(self):
        repository, files = utility.get_list_test_files()
        for filename in files:
            f = os.path.join(repository, filename)
            metadata = io.MetaDataReader(str(f))
            tfile = taglib.File(f)

            if 'GENRE' in tfile.tags:
                self.assertEqual(metadata.genre(), tfile.tags['GENRE'][0])
            else:
                self.assertTrue(not metadata.genre())

            if 'TITLE' in tfile.tags and tfile.tags['TITLE'][0] != 'untitled':
                self.assertEqual(metadata.title(), tfile.tags['TITLE'][0])
            else:
                self.assertTrue(not metadata.title())

            if 'ARTIST' in tfile.tags:
                self.assertEqual(metadata.artist(), tfile.tags['ARTIST'][0])
            else:
                self.assertTrue(not metadata.artist())

            if 'ALBUM' in tfile.tags:
                self.assertEqual(metadata.album(), tfile.tags['ALBUM'][0])
            else:
                self.assertTrue(not metadata.album())

            if 'TRACK' in tfile.tags:
                self.assertEqual(metadata.track(), tfile.tags['TRACK'][0])
            else:
                self.assertTrue(metadata.track() == 0)

            if 'YEAR' in tfile.tags:
                self.assertEqual(metadata.year(), tfile.tags['YEAR'][0])
            else:
                self.assertTrue(metadata.year() == 0)
