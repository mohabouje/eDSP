meow_fft
========

My Easy Oresome Wonderfull FFT

By Richard Maxwell

A simple, C99, header only, 0-Clause BSD Licensed, fast fourier transform (FFT).

Example
=======

```C
    #define MEOW_FFT_IMPLEMENTAION
    #include <meow_fft.h>

    #include <malloc.h>

    void main(char** argv, int argv)
    {
        (void) argv;
        (void) argc;

        unsigned          N   = 1024;
        float*            in  = malloc(sizeof(float) * N);
        Meow_FFT_Complex* out = malloc(sizeof(Meow_FFT_Complex) * N);

        // prepare data for "in" array.
        // ...

        size_t workset_bytes = meow_fft_generate_workset_real(N, NULL);
        // Get size for a N point fft working on non-complex (real) data.

        Meow_FFT_Workset_Real* fft_real =
            (Meow_FFT_Workset_Real*) malloc(workset_bytes);

        meow_fft_generate_workset_real(N, fft_real);

        meow_fft_real(fft_real, in, out);
        // out[0].r == out[0  ].r
        // out[0].j == out[N/2].r

        meow_fft_real_i(fft_real, in, out);
        // result is not scaled, need to divide all values by N

        free(fft_real);
        free(out);
        free(in);
    }
```

Usage
=====

Since this is a single header library, just make a C file with the lines:

```C
    #define MEOW_FFT_IMPLEMENTAION
    #include <meow_fft.h>
```

There are two sets of functions. Ones dealing with sequential interleaved
floating point complex numbers, and ones dealing with sequential floating point
real numbers (postfixed with `_real`).

Forward FFTs are labelled `_fft` while reverse FFTs are labelled `_fft_i`.

The function `_is_slow` can be used to tell if you have a non-optimised radix
calculation in your fft (ie the slow DFT is called). This will also increase
the memory requirements required by the workset.

All functions are namespaced with `meow_` and all Types by `Meow_`.


Why?
====
I thought I could write a faster FFT that kiss_fft, since I couldn't use FFTW3
due to its GPL license. LOL, If I knew about the pffft library, I would have
just used that instead.

`¯\_(ツ)_/¯`

Performance
===============

* This FFT is for people who want a single file FFT implementation without any
licensing headaches and are not concerned with having the fastest performance.

* This FFT is for people wanting to know how a fft is written using a _simple-ish_
  implementation
* It doesn't explicitly use vectorised instructions (SSE, NEON, AVX)
* It is faster than kiss_fft only due to using a radix-8 kernel
* It is slower than pffft, muFFT, vDSP, FFTW and other accelerated FFT libraries
* It is slower than anything on the GPU
* It has not been tested _on_ a GPU

I found changing compiler flags can make the FFT go faster _or_ slower depending
on what you want to do. For example, using gcc with `-march=native` on my i7
resulted in the > 2048 FFTs going faster, but the < 2048 FFTs going twice as
slow. I also got mixed results with `-ffast-math`. Basically, you need to figure
out what FFTs you are going to use, and then benchmark various compiler options
for your target platforms in order to get any useful compiler based performance
increases.


Reading List
============

* It's a circle! -> How FFTs _actually_ work
  http://betterexplained.com/articles/an-interactive-guide-to-the-fourier-transform/

* How to get radix-2, 3, 4, and 5 formulas:
  http://www.briangough.com/fftalgorithms.pdf pages 18 and 19

* How do make a faster fft when only dealing with real (non-complex) inputs.
  (Warning, the maths is confusing due to inconsistent formulas and assumptions)
  http://www.engineeringproductivitytools.com/stuff/T0001/PT10.HTM

* Finally, know that ffts are pretty much as fast as you can get, you need
  to start making them cache friendly to get any extra speed.
  https://math.mit.edu/~stevenj/18.335/FFTW-Alan-2008.pdf

* Hmm, how is it done on GPUs? 
  http://mc.stanford.edu/cgi-bin/images/7/75/SC08_FFT_on_GPUs.pdf

FFT Implementation
==================

I have implemented a non-scaled, float based decimation in time, mixed-radix,
out of place, in order result fast fourier tansform with sequentially accessed
twiddle factors per stage, with seperate forward and reverse functions. It has
custom codelets for radices: 2,3,4,5 and 8, as well as a slow general discrete
fourier transform (DFT) for all other prime number radices.

Secondly, I have also a real only FFT that uses symetrical based mixing in order
to do a two for one normal FFT using real data.

I wrote my FFT using kiss_fft, and engineeringproductivitytools as a guide, as
well as many days and nights going "wtf, I have no idea what I'm doing". I used
FFTW's fft codelet compilers to generate my radix-8 codelet, as doing code
simplification by hand would have taken me another six months.

All in all it took me one year of part time coding to get this releasable.

Could be faster if
------------------

* I don't reorder the fft, so the result is all jumbled up, and you need a 2nd
  function to reorder it (like pffft)

* Write ISPC code in case vectorisation can make it go faster


Benchmarks
==========

Test Platforms
--------------

| Platform                                     | GCC version |
|----------------------------------------------|-------------|
| Intel(R) Core(TM) i7-4790 CPU     @ 3.60GHz  | 6.3.1       |
| ARMv7 Processor rev 10 (v7l)      @ 1.00 GHz | 4.8.1       |
| Intel(R) Core(TM)2 Duo CPU P8400  @ 2.26GHz  | 6.3.0       |

Build Line
----------

All builds used GCC with `-O2 -g`. The ARM build use the command line options:

```
    -march=armv7-a -mthumb-interwork -mfloat-abi=hard -mfpu=neon
    -mtune=cortex-a9
```

Measurement Procedure
---------------------

The time taken to do an N point FFT every 32 samples of a 5 second 16 bit mono
44.1Khz buffer (signed 16 bit values) was mesasued. This was then divided by
the number of FFT calculations performed to give a value of microseconds per
FFT. This was done 5 times and the median value was reported.

Results for meow_fft, kiss_fft, fftw3 and pffft were taken. fftw was not tested
on the ARM platform. Some tests for pffftw were skipped due to lack of support
for certain values of N. pffft uses SSE/NEON vector CPU instructions.

*NOTE* FFTW3 results are currently wrong as its using hartly instead of real
FFT transform. Updated benchmarks are pending...

Results
-------

Values are microseconds per FFT (1,000,000 microseconds are in one second)

### Power of Two values of N

#### Intel(R) Core(TM) i7-4790 CPU @ 3.60GHz

|     N |   meow |   kiss |  pffft |  fftw3 |
|-------|--------|--------|--------|--------|
|    64 |   0.73 |   0.58 |   0.15 |   0.15 |
|   256 |   2.32 |   3.49 |   0.44 |   1.45 |
|   512 |   4.36 |   5.09 |   1.02 |   3.35 |
|  1024 |   8.89 |  13.12 |   2.19 |   7.29 |
|  2048 |  23.00 |  24.61 |   5.27 |  16.26 |
|  4096 |  42.30 |  60.04 |  11.09 |  35.49 |
|  8192 |  84.72 | 119.38 |  39.49 |  84.72 |
| 16384 | 232.20 | 290.22 |  82.47 | 189.40 |
| 32768 | 411.35 | 562.56 | 208.15 | 417.32 |

#### Intel(R) Core(TM)2 Duo CPU P8400  @ 2.26GHz

|     N |   meow |    kiss |  pffft |
|-------|--------|---------|--------|
|    64 |   0.87 |    1.45 |   0.29 |
|   256 |   5.52 |    6.97 |   1.16 |
|   512 |  10.04 |   11.93 |   2.47 |
|  1024 |  19.39 |   32.95 |   4.81 |
|  2048 |  53.47 |   59.19 |  11.43 |
|  4096 |  99.23 |  150.40 |  24.55 |
|  8192 | 196.56 |  283.24 |  72.81 |
| 16384 | 523.36 |  708.37 | 150.36 |
| 32768 | 975.28 | 1357.65 | 337.54 |

#### ARMv7 Processor rev 10 (v7l) @ 1.00 GHz

|     N |    meow |    kiss |   pffft |
|-------|---------|---------|---------|
|    64 |    4.94 |    7.69 |    3.77 |
|   256 |   25.86 |   32.26 |   12.64 |
|   512 |   44.37 |   54.84 |   28.22 |
|  1024 |   84.14 |  146.84 |   57.45 |
|  2048 |  255.79 |  280.98 |  147.82 |
|  4096 |  497.34 |  758.80 |  326.23 |
|  8192 | 1025.47 | 1502.71 |  847.75 |
| 16384 | 2822.83 | 3891.50 | 1831.14 |
| 32768 | 5434.37 | 9110.81 | 4220.76 |

### Non Power of Two values of N

#### Intel(R) Core(TM) i7-4790 CPU @ 3.60GHz

|     N |   meow |   kiss |  pffft |  fftw3 |
|-------|--------|--------|--------|--------|
|   100 |   0.87 |   0.87 |        |   0.58 |
|   200 |   1.74 |   1.89 |        |   1.16 |
|   500 |   5.96 |   5.82 |        |   3.78 |
|  1000 |  10.79 |  12.10 |        |   8.02 |
|  1200 |  13.72 |  15.18 |        |   9.78 |
|  5760 |  77.65 |  88.97 |  20.72 |  56.78 |
| 10000 | 130.74 | 160.23 |        | 119.95 |

#### Intel(R) Core(TM)2 Duo CPU P8400  @ 2.26GHz

|     N |   meow |   kiss |  pffft |
|-------|--------|--------|--------|
|   100 |   2.47 |   2.03 |        |
|   200 |   4.50 |   4.36 |        |
|   500 |  15.27 |  12.95 |        |
|  1000 |  28.14 |  27.26 |        |
|  1200 |  34.44 |  36.04 |        |
|  5760 | 194.78 | 208.94 |  47.24 |
| 10000 | 341.90 | 350.11 |        |

#### ARMv7 Processor rev 10 (v7l) @ 1.00 GHz

|     N |    meow |    kiss |  pffft |
|-------|---------|---------|--------|
|   100 |   11.91 |   10.45 |        |
|   200 |   19.47 |   19.76 |        |
|   500 |   67.93 |   58.33 |        |
|  1000 |  117.51 |  116.93 |        |
|  1200 |  156.87 |  175.98 |        |
|  5760 |  923.85 | 1163.04 | 612.37 |
| 10000 | 1677.87 | 1985.10 |        |

### Accuracy

In a perfect world, doing an FFT then an inverse FFT on the same data, then
scaling the result by 1/N should result in an identical buffer to the source
data. However in real life, floating point errors can accumulate.

The first 32 values of the input data were compaired to a scaled result buffer
and then the difference multiplied by 65536 to simulate what the error would be
for a 16 bit audio stream using 32 bit floating point FFT maths. The worst error
of the first 32 values was recorded for each FFT tested for size N.

|   FFT |   Min |   Max |
|-------|-------|-------|
| meow  | 0.016 | 0.031 |
| kiss  | 0.016 | 0.029 |
| pffft | 0.012 | 0.043 |
| fftw3 | 0.000 | 0.000 |


Other FFT Implementations
=========================

* FFTW3    (GPL) : the original library, best accuracy.
  http://www.fftw.org/

* kiss_fft (BSD) : small and simple to follow, not as fast as fftw.
  https://github.com/itdaniher/kissfft (mirror)

* pffft (FFTPACK): Sometimes faster than FFTW3! More accurate than kiss or meow.
  https://bitbucket.org/jpommier/pffft

* FFTS     (MIT) : I couldn't get it to compile :-(
  https://github.com/anthonix/ffts
  
* muFFT    (MIT) : SSE, SSE3, AVX-256
  https://github.com/Themaister/muFFT
  
* GPU_FFT (3-BSD): GPU accelerated FFT for Rasberry Pi
  http://www.aholme.co.uk/GPU_FFT/Main.htm
