Size = 128;
format long
Array = fft(hamming(Size));
csvwrite('fft_hamming.csv', Array);

Array = fft(hann(Size));
csvwrite('fft_hanning.csv', Array);

Array = fft(blackman(Size));
csvwrite('fft_blackman.csv', Array);

Array = fft(blackmanharris(Size));
csvwrite('fft_blackman_harris.csv', Array);

Array = fft(nuttallwin(Size));
csvwrite('fft_blackman_nuttall.csv', Array);

Array = fft(bartlett(Size));
csvwrite('fft_bartlett.csv', Array);

Array = fft(bohmanwin(Size));
csvwrite('fft_bohman.csv', Array);

Array = fft(boxcar(Size));
csvwrite('fft_boxcar.csv', Array);

Array = fft(flattopwin(Size));
csvwrite('fft_flattop.csv', Array);
