%% Generate the different files for testing with different inputs

database_folder = [pwd, '/', 'database'];
mkdir(database_folder)
cd(database_folder)

% Generate files for a hamming windows


data_name = 'Hamming';
mkdir(data_name)
data = hamming(1024);
generate_testfiles(data, [database_folder, '/', data_name ], 6);

data_name = 'Hanning';
mkdir(data_name)
data = hanning(1024);
generate_testfiles(data, [database_folder, '/', data_name ], 6);