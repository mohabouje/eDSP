from pyperform import BenchmarkedFunction


@BenchmarkedFunction(largs=(1 << 12,), timeit_number=3, timeit_repeat=100)
def ConvolveNumpy(size):
    import numpy
    left = numpy.hamming(size)
    right = numpy.hanning(size)
    return numpy.convolve(left, right)

@BenchmarkedFunction(largs=(1 << 12,), timeit_number=3, timeit_repeat=100)
def ConvolvePedsp(size):
    import pedsp
    left = pedsp.windowing.hamming(size)
    right = pedsp.windowing.hanning(size)
    return pedsp.spectral.conv(left, right)

@BenchmarkedFunction(largs=(1 << 12,), timeit_number=3, timeit_repeat=100)
def CorrelationNumpy(size):
    import numpy
    left = numpy.hamming(size)
    right = numpy.hanning(size)
    return numpy.correlate(left, right, "full")

@BenchmarkedFunction(largs=(1 << 12,), timeit_number=3, timeit_repeat=100)
def CorrelationPedsp(size):
    import pedsp
    left = pedsp.windowing.hamming(size)
    right = pedsp.windowing.hanning(size)
    return pedsp.spectral.xcorr(left, right)