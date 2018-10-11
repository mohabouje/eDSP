format long
Array = fft(hamming(128));
Array = [real(Array), imag(Array)];
csvwrite('fft_hamming.csv', Array);

Array = fft(hann(256));
Array = [real(Array), imag(Array)];
csvwrite('fft_hanning.csv', Array);

Array = fft(blackman(2048));
Array = [real(Array), imag(Array)];
csvwrite('fft_blackman.csv', Array);
