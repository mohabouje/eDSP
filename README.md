# easy DSP

![releases](https://img.shields.io/github/tag/mohabouje/eDSP.svg)
![issues](https://img.shields.io/github/issues/mohabouje/eDSP.svg)
![license](https://img.shields.io/github/license/mohabouje/eDSP.svg)
![built](https://img.shields.io/badge/built%20with-GCC-6f62ba.svg)
[![FOSSA Status](https://app.fossa.io/api/projects/git%2Bgithub.com%2Fmohabouje%2FeDSP.svg?type=shield)](https://app.fossa.io/projects/git%2Bgithub.com%2Fmohabouje%2FeDSP?ref=badge_shield)

[![GitHub forks](https://img.shields.io/github/forks/mohabouje/eDSP.svg?style=social&label=Fork)]()
[![GitHub stars](https://img.shields.io/github/stars/mohabouje/eDSP.svg?style=social&label=Star)]()
[![GitHub watchers](https://img.shields.io/github/watchers/mohabouje/eDSP.svg?style=social&label=Watch)]()

**easyDSP** is a digital signal processing library written in C/C++ that implements some of the common functions and algorithms frequently used in digital signal processing & telecommunications systems. 

It aims to provide efficient and streamlined base calculations while at the same time having a straightforward and easy-to-use interface similar to another numeric language like [MATLAB](https://www.mathworks.com/products/matlab.html). 

***The library is under construction.***

<img src="https://openclipart.org/image/2400px/svg_to_png/293844/under-construction_geek_man_01.png" width="250">

### How to install it?

The easyDSP project is a header-only library with basic dependencies:

- FFTW: to compute the different Fourier transform
- libsamplerate: to apply some re-sample functionalities.
- If you are an Unix user, those libraries can be downloaded in a simple way. Example: using apt:

```bash
sudo apt-get install libfftw3-dev libsamplerate0-dev
```

The library also relies on a **C++14** compiler and the standard library (STL). Link the different libraries,  download the project and add the include/directory to  your compiler's header search path and you are done.

The easy way to enable/disable the different modules of the framework is by using the [ccmake](https://cmake.org/cmake/help/v3.0/manual/ccmake.1.html).

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
  - [x] Sinusoidal Oscillator
  - [x] Square Oscillator
  - [x] Triangular Oscillator
  - [x] Sawtooth Oscillator

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

