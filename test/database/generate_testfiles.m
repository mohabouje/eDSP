function [] = generate_testfiles( input, folder_path, precision )
    data_fft = fft(input);
    data_spectogram = abs(data_fft).^2;
    data_ifft = real(ifft(input));
    data_dct = dct(input);
    data_idct = real(idct(input));
    
    dlmwrite(get_filepath(folder_path, 'data_input.data'), input, 'delimiter', '\t', 'precision', precision);
    dlmwrite(get_filepath(folder_path, 'data_fft.data'), data_fft, 'delimiter', '\t', 'precision', precision);
    dlmwrite(get_filepath(folder_path, 'data_ifft.data'), data_ifft, 'delimiter', '\t', 'precision', precision);
    dlmwrite(get_filepath(folder_path, 'data_spectrogram.data'), data_spectogram, 'delimiter', '\t', 'precision', precision);
    dlmwrite(get_filepath(folder_path, 'data_dct.data'), data_dct, 'delimiter', '\t', 'precision', precision);
    dlmwrite(get_filepath(folder_path, 'data_idct.data'), data_idct, 'delimiter', '\t', 'precision', precision);

end

function [filepath] = get_filepath(folder_path, file_name) 
    filepath = [folder_path, '/', file_name];
end