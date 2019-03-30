# eDSP for C developers

Here you can find a binding for C developers. This library brings the opportunity
to link the original eDSP library into a C project.

The idea is not as crazy as it sounds, **the wrapper is C++ but exposes itself as C**,
that's why it has to be compile as C++ in order to use all the C++ features properly.

After compiling the library with a C++ compiler, you can link it an use it with any
standard C compiler.


###### Example: Fourier Transform of a Hamming window

This example shows how to compute the Fourier Transform of a Hamming Window using the
C bindings that eDSP provides.

```
// Define the size of the window
const int size = 100;

// Get the size of the fft for a real-to-complex conversion
const int fft_size = get_fft_size(size);

// Allocate the memory
real_t input_data[size];
complex_t output_data[fft_size];

// Initialize the Hamming window
hamming(input_data, size);

// Compute the fft
fft(input_data, size, output_data);
```