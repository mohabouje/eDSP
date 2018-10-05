format long
Array = xcorr(hamming(36), 'none');
Array = Array(length(Array)/2:end);
csvwrite('xcorr_hamming.csv', Array);

Array = xcorr(hann(257), 'none');
Array = Array(length(Array)/2:end);
csvwrite('xcorr_hanning.csv', Array);

Array = xcorr(blackman(2048), 'none');
Array = Array(length(Array)/2:end);
csvwrite('xcorr_blackman.csv', Array);