function Hf = fht(f)
    F = fft(f);
    Hf = real(F) - imag(F);
end

