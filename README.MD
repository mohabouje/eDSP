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


1. [Windowing](https://github.com/mohabouje/eDSP/wiki/Windowing)
2. [Oscillators](https://github.com/mohabouje/eDSP/wiki/Oscillators)
3. [Discrete Frequency Transform](https://github.com/mohabouje/eDSP/wiki/Discrete-Frequency-Transform)

***The library is under construction.***

<img src="https://openclipart.org/image/2400px/svg_to_png/293844/under-construction_geek_man_01.png" width="250">

## Compilation Flags

|Feature|State|Compilation Flag |
|--|--|--|
|Random Generators| Not Implemented Yet| `COMPILE_RANDOM_MODULE` |
|[Discrete Frequency Transform](https://github.com/mohabouje/eDSP/wiki/Discrete-Frequency-Transform)| Not Documented Yet| `COMPILE_FREQUENCY_MODULE` |
|Feature Extraction | Work In Progress| `COMPILE_FEATURES_EXTRACTION_MODULE` |
|[Windowing](https://github.com/mohabouje/eDSP/wiki/Windowing)| Done| `COMPILE_WINDOWING_MODULE` |
|[Oscillators](https://github.com/mohabouje/eDSP/wiki/Oscillators)| Done| `COMPILE_OSCILLATORS_MODULE` |
|IIR Filters| Not Documented Yet| `COMPILE_IIR_MODULE` |
|FIR Filters| Not Implemented Yet| `COMPILE_FIR_MODULE` |
|Modulation| Not Implemented Yet| `COMPILE_MODULATION_MODULE` |
|Statistics|Not Implement Yet| `COMPILE_STATISTICS_MODULE` |

## Compilation

The source code has been tested in Ubuntu 16.04 and MacOS 10.13 (High Sierra).

    mkdir build
    cd build
    cmake ..
    make -j4

The easy way to enable/disable the different modules of the framework is by using the [ccmake](https://cmake.org/cmake/help/v3.0/manual/ccmake.1.html).


### Example: Windowing an imput signal
This example show how to apply a Hamming window to an input signal $x(n)$ and store the output in a signal $y(n)$:
```c++
constexpr std::size_t size = 1024;
auto x = std::vector<double>(size);
auto y = std::vector<double>(size);

// Create a Hamming Window of 1024 samples
auto window = Hamming(size);

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
std::generate_n(std::begin(square), size,square_oscillator); 
```
### Example: Extract signal features
This example show how to extract_implementation some features like the energy and power of an input signal.

```c++
constexpr std::size_t size = 1024;
// Generate a buffer of a sin function
const auto real_data = std::vector<doubl>(size);
... 
// Extract the features from the input signal
const auto energy = properties::energy(std::cbegin(input), std::cend(input));
const auto power = properties::power(std::cbegin(input), std::cend(input));
```

### Example: Computing the DFT
This example show how to compute the DFT of an input signal.
```c++
constexpr std::size_t size = 1024;
// Generate a buffer of a sin function
auto real_data = std::vector<double>(size);

...

// Create an array of complex data to store the fft output
auto fft_data = std::vector<std::complex<double>>(size) fft_data;

// Create an fft object with the expected output size as parameter
FFT fft(size);
fft.compute(std::cbegin(real_data), std::cend(real_data), std::begin(fft_data));
```
