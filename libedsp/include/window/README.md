## Windowing

Most digital signals are infinite, or sufficiently large that the dataset cannot be manipulated as a whole. In order to avoid these problems, engineers typically analyze small subsets of the total data, through a process called **windowing**.

Application of a window to a dataset will **alter the spectral properties** of that dataset. Normally, all the data points outside the window are truncated and therefore assumed to be zero. *The cut-off points at the ends of the sample will introduce high-frequency components*.

Consider the system $H(z)$, with input $X(z)$ and output $Y(z)$. We model this as:

$\displaystyle Y(z)=X(z)H(z)$

If we have a window with transfer function $W(z)$, we can mathematically apply the window to our signal, $X(z)$ as such:

$\hat{X} ( z ) = X ( z ) W ( z )$

Then, we can pass our windowed signal into our system, $H(z)$ as usual:

$\displaystyle {\hat {Y}(z)=\hat {X}(z)H(z)}$ 

eDSP integrate a set of the most common used windows that implements a simple interface to apply those operations. 

 - Hamming
 - Hanning
 - Blackman
 - Blackman-Harris
 - Blackman-Nuttall
 - Bartlett
 - Kaiser
 - Parzen
 - Rectangular
 - Gaussian
 - Barthann
 - Bohman
 - Triangular
 - Tukey
 - Welch
- Flat-Top

***Example***: Apply a Hamming window to an input signal $x(n)$ and store it in a output signal $y(n)$:
```c++
constexpr std::size_t size = 1024;
auto x = std::vector<double>(size);
auto y = std::vector<double>(size);

// Create a Hamming Window of 1024 samples
auto window = std::make_unique<Hamming>(size);

// Apply the window to the signal X and store it in Y
window->compute(std::cbegin(x), std::cend(x), std::begin(y));
```




