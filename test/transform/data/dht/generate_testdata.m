Size = 128;
format long

Array = fht(hamming(Size));
csvwrite('dht_hamming.csv', Array);

Array = fht(hann(Size));
csvwrite('dht_hanning.csv', Array);

Array = fht(blackman(Size));
csvwrite('dht_blackman.csv', Array);
