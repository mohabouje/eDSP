Size = 128;
format long
Array = hilbert(hamming(Size));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_hamming.csv', Array);

Array = hilbert(hann(Size));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_hanning.csv', Array);

Array = hilbert(blackman(Size));
Array = [real(Array), imag(Array)];
csvwrite('hilbert_blackman.csv', Array);