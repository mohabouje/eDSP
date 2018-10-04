# easy DSP

![releases](https://img.shields.io/github/tag/mohabouje/eDSP.svg)
![issues](https://img.shields.io/github/issues/mohabouje/eDSP.svg)
![license](https://img.shields.io/github/license/mohabouje/eDSP.svg)
![built](https://img.shields.io/badge/built%20with-GCC-6f62ba.svg)
[![Build Status](https://travis-ci.org/mohabouje/eDSP.svg?branch=master)](https://travis-ci.org/mohabouje/eDSP)

[![GitHub forks](https://img.shields.io/github/forks/mohabouje/eDSP.svg?style=social&label=Fork)]()
[![GitHub stars](https://img.shields.io/github/stars/mohabouje/eDSP.svg?style=social&label=Star)]()
[![GitHub watchers](https://img.shields.io/github/watchers/mohabouje/eDSP.svg?style=social&label=Watch)]()

**easyDSP** is a digital signal processing library written in C/C++ that implements some of the common functions and algorithms frequently used in digital signal processing & telecommunications systems. 

It aims to provide efficient and streamlined base calculations while at the same time having a straightforward and easy-to-use interface similar to another numeric language like [MATLAB](https://www.mathworks.com/products/matlab.html). 



***The library is under construction.***

<img src="https://openclipart.org/image/2400px/svg_to_png/293844/under-construction_geek_man_01.png" width="250">

### Why other DSP library?

The *easyDSP* project is a modern C++ DSP library that:

- Aims to be ***cross-platform***
- Has a modern ***STL-like API***
- Supports modern ***C++11/14/17 features***
- Integrates bindings for different languages: ***Python & Go***

### Documentation

Latest development documentation is available [online]().

### Dependencies

The *easyDSP* project is a header-only library that relies on a **C++14** compiler and the standard library (STL). A recent version of CMake is required. The minimum is 3.4, but tested primarily with 3.6 and newer.

Those are the list of external tools dependencies:

| Library                                            | Dependencies | Description                                                  |
| -------------------------------------------------- | ------------ | ------------------------------------------------------------ |
| [libfftw](http://www.fftw.org/)                  | Spectral     | Integrates one of the fastest FFT implementations.           |
| [libsamplerate](http://www.mega-nerd.com/SRC/)   | Codec        | Integrates an efficient re-sampling algorithm.               |
| [libaudiofile](https://audiofile.68k.org/)       | Codec        | Integrates an efficient decoder/encoder for different audio formats. |
| [libsndfile](http://www.mega-nerd.com/libsndfile/) | Codec        | Integrates an efficient  decoder/encoder for different audio formats. |
  [libgtest-dev](https://github.com/google/googletest) | Test | Integrates a simplest and modern framework for testing. |
### How to install it?

The *easyDSP* project is a header-only library with basic dependencies. Link them,  download the project and add the include/directory to  your compiler's header search path and you are done.

If you want to install the library and make it accessible to all resources in your system, follow those steps:

1. Download the source code

   Clone the repository from github or download the latest version from this [link]().

   ```bash
   git clone https://github.com/mohabouje/eDSP.git --recursive
   cd eDSP
   ```

2. Build the library

   The build system uses CMake. The procedure is standard for CMake builds:

   ```bash
   mkdir build	
   cd build
   cmake -DCMAKE_BUILD_TYPE=Release ..
   make -jN
   ```

   The user can enable/disable the different packages independently, probably the easy way to do so by using  [ccmake](https://cmake.org/cmake/help/v3.0/manual/ccmake.1.html). More details about *easyDSP* configuration options are located in the [User Documentation]().

3. Building the tests

   Install the different dependencies:

   ```bash
   sudo apt-get install libfftw3-dev libsamplerate0-dev libaudiofile-dev libsndfile1-dev
   ```

   To run all the test, use:

   ```bash
   make test
   ```

4. Building the examples

   Several examples demonstrating specific usages can be found in the [examples](https://github.com/mohabouje/eDSP/master/examples) folder of the repository. More useful examples can be found on the [eDSP Wikie](https://github.com/mohabouje/eDSP/wiki).

   To build the examples, use:

   ```bash
   make examples
   ```

   If you want to run an individual example, those are in subdirectories in examples (built products are in your build directory, the source is in   [examples](https://github.com/mohabouje/eDSP/master/examples) folder).

5. Building the docs

   The docs are available in different formats, for instance: html & latex. To build the docs, use:

   ```bash
   make html
   ```

   Also, the latest development documentation is available [online]().

6. Installing the library:

   ```bash
   sudo make install
   ```

### License

Copyright (c) 2018, Mohammed Boujemaoui Boulaghmoudi (mohabouje@gmail.com), All rights reserved.

Distributed under the [GPLv3 license](https://www.gnu.org/licenses/gpl-3.0.html).

======================================================================================

## TODO
- [ ] Test the different features [WIP]
- [ ] Benchmark the library [WIP]
- [ ] Write Documentation [WIP]
- [ ] Python Wrapper
- [ ] Open-Frameworks Wrapper
- [x] Compile time optimizations: constexpr & traits
- [x] Modern C++: const method, noexcept construction, contract, assertions...

## Features

Those are the list of features that are implemented or scheduled to be. All of those features will be wrapped in to a Python & JavaScript binding to allow an easy with third party tools.

- [x] Pre-Processing Techniques
  - [x] Amplifier
  - [x] Clipper
  - [x] Mixer
  - [x] Normalizer
  - [x] Resampler
  - [x] Search
  - [x] Lin-space
  - [x] Log-space
  - [x] Padder
  - [x] Normalizer
  - [ ] Frame Cutter
  - [ ] Splitter

- [x] Implementing basic discrete transforms
  - [x] DFT : Discrete Fourier Transform
  - [x] DCT: Discrete Cosine Transform
  - [x] Discrete Hilbert Transform
  - [x] Discrete Hartley Transform

- [ ] Digital Filters
  - [x] FIR : Finite Impulse Response filter
  - [ ] IIR : Infinite Impulse Response filter
  - [x] Butterworth Filters
  - [x] Chebishev I && Chebishev II Filters
  - [ ] Elliptic Filters
  - [ ] Legendre Filters
  - [ ] Bessel Filters
  - [x] RBJ Filters
  - [x] Zolzer Filters
  - [x] Moving Average Filter
  - [x] Moving Median Filter
  - [x] Moving RMS Filter

- [x] Windowing 
  - [x] Bartlett
  - [x] Blackman
  - [x] Flat-Top
  - [x] Hamming
  - [x] Hanning
  - [x] Triangular
  - [x] Blackman - Harris
  - [x] Blackman - Nuttal
  - [x] Bartlett - Hann
  - [ ] Kaiser
  - [ ] Gauss

- [x] Implement basic oscillators
  - [x] Sinusoidal oscillator
  - [x] Square oscillator
  - [x] Triangular oscillator
  - [x] Sawtooth oscillator

- [ ] Spectral
  - [x] Auto Correlation
  - [x] Cross Correlation
  - [x] Convolution
  - [x] Spectrum
  - [x] Cepstrum
  - [ ] LPC: Linear Predictive Coefficients
  - [ ] Cepstral LPC
  - [ ] Filter Banks
    - [ ] Mel Filter Banks
    - [ ] Bark Filter Banks
    - [ ] Gamma Tone Filter Banks
    - [ ] ERB Filter Banks

- [x] Statistical Properties
  - [x] Histogram
  - [x] Mean
  - [x] Moment
  - [x] Variance
  - [x] Skewness
  - [x] Covariance

- [x] Tools

  - [x] DC Removal
  - [x] De-Emphasis
  - [x] Pre-Emphasis
  - [x] Envelope Follower


### Example: Windowing an imput signal

This example show how to apply a Hamming window to an input signal $x(n)$ and store the output in a signal $y(n)$:

```c++
using namespace easy::dsp;

constexpr std::size_t size = 1024;
auto x = std::vector<double>(size);
auto y = std::vector<double>(size);

// Create a Hamming Window of 1024 samples
auto window = make_window<Hamming>(size);

// Apply the window to the signal X and store it in Y
window.compute(std::cbegin(x), std::cend(x), std::begin(y));
```

### Example: Generate an square signal

This example show how to generate a square wave with a duration of 10 seconds, frequency of 500Hz and sampled at 8000Hz.

```c++
const std::size_t size = 80000;
std::vector<double> square(size);

// Configure the oscillator
auto square_oscillator = SquareOscillator();
square_oscillator.set_samplerate(8000);
square_oscillator.set_amplitude(2);
square_oscillator.set_frequency(500);

// Generate the samples and store them
std::generate_n(std::begin(square), size, square_oscillator); 
```

### Example: Computing the DFT

This example show how to compute the DFT of an input signal.

```c++
constexpr std::size_t size = 1024;
// Generate a buffer of a sin function
auto real_data = std::vector<double>(size);

...

// Create an array of complex data to store the fft output
auto fft_data = std::vector<std::complex<double>>(size );

// Create an fft object with the expected output size as parameter
easy::dsp::complex_dft(std::cbegin(real_data), std::cend(real_data), std::begin(fft_data));
```

