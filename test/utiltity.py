import scipy.signal as sp
import numpy as np
from random import randint


def get_generators():
    return [sp.hamming, sp.hann, sp.flattop, sp.nuttall, sp.blackman, sp.parzen]


def generate_inputs(number_inputs, minimum_size, maximum_size):
    signals = get_generators()
    data = []
    for i in range(0, number_inputs):
        size = randint(minimum_size, maximum_size)
        data.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + 0.1)
    return data


def generate_pair_inputs(number_inputs, minimum_size, maximum_size):
    signals = get_generators()
    first = []
    second = []
    for j in range(0, number_inputs):
        size = randint(minimum_size, maximum_size)
        first.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + 0.1)
        second.append(signals[randint(0, len(signals) - 1)](size).astype(np.float64) + 0.1)
    return first, second
