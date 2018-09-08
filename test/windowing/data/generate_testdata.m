Size = 128;
format long
Array = hamming(Size);
csvwrite('hamming.csv', Array);

Array = hann(Size);
csvwrite('hanning.csv', Array);

Array = blackman(Size);
csvwrite('blackman.csv', Array);

Array = blackmanharris(Size);
csvwrite('blackman_harris.csv', Array);

Array = nuttallwin(Size);
csvwrite('blackman_nuttall.csv', Array);

Array = bartlett(Size);
csvwrite('bartlett.csv', Array);

Array = bohmanwin(Size);
csvwrite('bohman.csv', Array);

Array = boxcar(Size);
csvwrite('boxcar.csv', Array);

Array = flattopwin(Size);
csvwrite('flattop.csv', Array);
