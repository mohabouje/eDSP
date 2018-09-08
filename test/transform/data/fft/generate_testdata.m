Size = 128;
format long
Array = fft(hamming(Size));
Array = [real(Array), imag(Array)];
csvwrite('fft_hamming.csv', Array);

Array = fft(hann(Size));
Array = [real(Array), imag(Array)];
csvwrite('fft_hanning.csv', Array);

Array = fft(blackman(Size));
Array = [real(Array), imag(Array)];
csvwrite('fft_blackman.csv', Array);
