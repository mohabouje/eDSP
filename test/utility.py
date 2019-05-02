import scipy.signal as sp
import numpy as np
from random import randint
import os
import os.path
import soundfile as sf

epsilon = 0.1

def get_list_test_files():
    file_path = os.path.abspath(__file__)
    root = os.path.dirname(file_path)
    dir_path = os.path.join(root, "data")
    return dir_path, os.listdir(dir_path)

def read_audio_test_files(number_inputs, minimum_size, maximum_size):
    dir_path, files = get_list_test_files()
    data = []
    for _ in range(number_inputs):
        path = os.path.join(dir_path, files[randint(0, len(files) - 1)])
        wave, fs = sf.read(str(path))
        _, channels = wave.shape
        wave = wave.sum(axis=1) / channels
        wave = wave.astype(np.float64) + epsilon
        size = randint(min(minimum_size, len(wave)), min(maximum_size, len(wave)))
        starting = randint(0, len(wave) - size)
        wave = wave[starting:starting + size]
        data.append((fs, np.asarray(wave)))
    return data


def get_change(current, previous):
    if current == previous:
        return 0.0
    try:
        return (abs(current - previous) / previous) * 100.0
    except ZeroDivisionError:
        return 0

def get_generators():
    return [sp.hamming, sp.hann, sp.flattop, sp.nuttall, sp.blackman, sp.parzen]

def generate_inputs(number_inputs, minimum_size, maximum_size):
    signals = get_generators()
    data = []
    for _ in range(number_inputs):
        size = randint(minimum_size, maximum_size)
        data.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + epsilon)
    return data

def generate_pair_inputs(number_inputs, minimum_size, maximum_size):
    signals = get_generators()
    first = []
    second = []
    for _ in range(number_inputs):
        size = randint(minimum_size, maximum_size)
        first.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + epsilon)
        second.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + epsilon)
    return first, second

def generate_timestamps(init_t, n, sr):
    samples = np.zeros(shape=(n,), dtype=np.float64)
    period = 1.0 / sr
    temporal = init_t
    for i in range(n):
        samples[i] = temporal
        temporal = temporal + period
    return samples
