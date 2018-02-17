easy DSP
===================

![releases](https://img.shields.io/github/tag/mohabouje/eDSP.svg)
![issues](https://img.shields.io/github/issues/mohabouje/eDSP.svg)
![license](https://img.shields.io/github/license/mohabouje/eDSP.svg)
![built](https://img.shields.io/badge/built%20with-GCC-6f62ba.svg)

[![GitHub forks](https://img.shields.io/github/forks/mohabouje/eDSP.svg?style=social&label=Fork)]()
[![GitHub stars](https://img.shields.io/github/stars/mohabouje/eDSP.svg?style=social&label=Star)]()
[![GitHub watchers](https://img.shields.io/github/watchers/mohabouje/eDSP.svg?style=social&label=Watch)]()

**easy DSP** is an digital signal processing library written in C/C++ that implements most of the available functions and algorithms for signal processing & telecommunications systems. 

It aims to provide efficient and streamlined base calculations, while at the same time having a straightforward and easy-to-use interface similar to another numeric language like [MATLAB](https://www.mathworks.com/products/matlab.html). 

<i class="icon-hdd"></I> **The library is under constructions.**

><i class="icon-file"></i> **Actual State**
> - Implementation of different signal generators: white noise, pink noise, sin, square....
> - Implementation of the Basic statistic functions.
> - Developing the frequency analysis module: FFT, DCT, DHT....
> - Developing the signal properties analysis: energy, power, zero crossing rate ....
> - Windowing
> - Basic digital filter implementation using Biquad - WIP
> - Analog filter implementation - WIP

## Example: Extract signal properties
Given an input signal, eDSP allow the extraction of some of the basic properties of audio signals:

 - Energy
 - Power
 - Loudness using the Steven Low Level
 - Zero Crossing Rate
 - et...
Example of usage:

```c++
constexpr std::size_t size = 1024;
// Generate a buffer of a sin function
const auto real_data = generators::sin<double, size>(1000, 0, 2);

const auto energy = properties::energy(std::cbegin(input), std::cend(input));
const auto power = properties::power(std::cbegin(input), std::cend(input));
```

## Example: Frequency domain computation
This library uses the available implementation of the FFT in the [FFTW](http://www.fftw.org/) library.  It allows the computation of the generic frequency transforms:

 - (FFT) Fast Fourier Transform
 - (IFFT) Inverse Fast Fourier Transform
 - (DCT) Direct Cosine Transform (Type I, II, III & IV)
 - (IDCT) Inverse Direct Cosine Transform (Type I, II, III & IV)
 - (DHT) Discrete Hartley Transform

Example of usage:

```c++
constexpr std::size_t size = 1024;
// Generate a buffer of a sin function
const auto real_data = generators::sin<double, size>(1000, 0, 2);

// Create an array of complex data to store the fft output
std::array<std::complex<double>, size> fft_data;

// Create an fft object with the expected output size as parameter
FFT fft(size);
fft.compute(std::cbegin(real_data), std::cend(real_data), std::begin(fft_data));
