format long

Array = fht(hamming(128));
csvwrite('dht_hamming.csv', Array);

Array = fht(hann(512));
csvwrite('dht_hanning.csv', Array);

Array = fht(blackman(2048));
csvwrite('dht_blackman.csv', Array);
