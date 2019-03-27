format long
Array = hilbert(hamming(128));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_hamming.csv', Array);

Array = hilbert(hann(256));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_hanning.csv', Array);

Array = hilbert(blackman(2048));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_blackman.csv', Array);