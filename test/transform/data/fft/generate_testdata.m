format long
Array = fft(hamming(128));
Array = [real(Array), imag(Array)];
csvwrite('fft_hamming.csv', Array);

Array = fft(hann(513));
Array = [real(Array), imag(Array)];
csvwrite('fft_hanning.csv', Array);

Array = fft(blackman(2047));
Array = [real(Array), imag(Array)];
csvwrite('fft_blackman.csv', Array);
