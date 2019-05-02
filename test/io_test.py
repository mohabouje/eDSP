import unittest
import pedsp.io as io
import numpy as np
import utility
import random
import taglib
import os
import os.path
import uuid
import samplerate
from samplerate.converters import ConverterType
from pysndfile import *


class TestIOMethods(unittest.TestCase):

    __number_inputs = []
    __maximum_size = []
    __minimum_size = []
    __database = []

    def __init__(self, *args, **kwargs):
        self.__number_inputs = 10
        self.__maximum_size = 10000
        self.__minimum_size = 100
        self.__database = utility.read_audio_test_files(self.__number_inputs, self.__minimum_size, self.__maximum_size)
        super(TestIOMethods, self).__init__(*args, **kwargs)

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

    def test_decoder_open_file(self):
        repository, files = utility.get_list_test_files()
        for filename in files:
            f = os.path.join(repository, filename)
            decoder = io.Decoder()
            decoder.open(str(f))
            sndfile = PySndfile(f)
            self.assertTrue(decoder.is_open())
            self.assertEqual(sndfile.channels(), decoder.channels())
            self.assertEqual(sndfile.samplerate(), decoder.samplerate())

    def test_decoder_read_all_data(self):
        repository, files = utility.get_list_test_files()
        for filename in files:
            f = os.path.join(repository, filename)
            decoder = io.Decoder()
            decoder.open(str(f))

            sndfile = PySndfile(f)
            frames = sndfile.read_frames(dtype=np.float32)
            self.assertEqual(decoder.frames(), frames.shape[0])

            data = decoder.read(frames.size)
            data = data.reshape(frames.shape)
            np.testing.assert_array_almost_equal(frames, data)

    def test_decoder_seek(self):
        repository, files = utility.get_list_test_files()
        for filename in files:
            f = os.path.join(repository, filename)
            decoder = io.Decoder()
            decoder.open(str(f))

            sndfile = PySndfile(f)
            self.assertEqual(decoder.seekable(), sndfile.seekable())

            index = random.randint(0, decoder.frames() - 1)

            seek_counter_pedsp = decoder.seek(index)
            seek_counter_sndfile = sndfile.seek(index)
            self.assertEqual(seek_counter_pedsp, seek_counter_sndfile)

            remaining = decoder.frames() - seek_counter_pedsp
            frames = sndfile.read_frames(remaining, dtype=np.float32)
            data = decoder.read(frames.size)
            data = data.reshape(frames.shape)
            np.testing.assert_array_almost_equal(frames, data)

    def test_encoder(self):
        repository, _ = utility.get_list_test_files()
        number_inputs = 10
        minimum_size = 1 << 10
        maximum_size = 1 << 20
        sr = [8000, 11025, 22050, 32000, 44100, 48000]
        for data in utility.generate_inputs(number_inputs, minimum_size, maximum_size):
            samplerate = random.choice(sr)

            encoder = io.Encoder(samplerate, 1)
            self.assertEqual(samplerate, encoder.samplerate())
            self.assertEqual(1, encoder.channels())

            filename = str(uuid.uuid4()) + ".wav"
            f = os.path.join(repository, filename)

            encoder.open(f)
            self.assertTrue(encoder.is_open())

            counter = encoder.write(data.astype(np.float32))
            self.assertEqual(data.size, counter)

            encoder.close()

            decoder = io.Decoder()
            decoder.open(f)
            self.assertEqual(len(data), decoder.frames())
            self.assertEqual(samplerate, decoder.samplerate())
            self.assertEqual(1, decoder.channels())

            recovery = decoder.read(len(data))
            np.testing.assert_array_almost_equal(recovery, data)

            decoder.close()
            os.remove(f)

    def test_resampler(self):
        sr = [8000, 11025, 22050, 32000, 44100, 48000]
        q = [io.ResampleQuality.Linear,
             io.ResampleQuality.MediumQuality,
             io.ResampleQuality.BestQuality,
             io.ResampleQuality.Fastest,
             io.ResampleQuality.ZeroOrderHold]
        eq = {io.ResampleQuality.Linear: ConverterType.linear,
              io.ResampleQuality.MediumQuality: ConverterType.sinc_medium,
              io.ResampleQuality.BestQuality: ConverterType.sinc_best,
              io.ResampleQuality.Fastest: ConverterType.sinc_fastest,
              io.ResampleQuality.ZeroOrderHold: ConverterType.zero_order_hold}

        for old_samplerate, data in self.__database:
            alternative_samplerates = list(filter(lambda x: x >= old_samplerate, sr))
            new_samplerate = random.choice(alternative_samplerates)
            ratio = new_samplerate / old_samplerate
            self.assertTrue(io.Resampler.valid_ratio(ratio))

            algorithm = random.choice(q)
            channels = 1

            resampler = io.Resampler(channels, algorithm, ratio)
            self.assertEqual(algorithm, resampler.quality())
            self.assertAlmostEqual(ratio, resampler.ratio(), 4)
            self.assertEqual(0, resampler.error())

            # data = (data + utility.epsilon) * 100
            # resampled, _ = resampler.process(data.astype(np.float32))
            # self.assertTrue(len(resampled) <= len(data) * ratio)

            # res = samplerate.Resampler(eq[algorithm], channels=channels)
            # reference = res.process(data, ratio, end_of_input=False)
            # for l, r in zip(np.round(resampled), np.round(reference)):
            #     error = utility.get_change(l, r)
            #     self.assertTrue(error < 1)
