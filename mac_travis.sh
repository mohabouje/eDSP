#!/bin/bash

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m' # No Color
BG='\033[0;32m' # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
allert () { echo -e "${RED}$1${NC}"; }

export PATH=/usr/local/bin:/usr/local/sbin:$PATH

showinfo "Installing third-party tools"
# TODO: replace by brew install
pip3 install -U ipython numpy matplotlib pyyaml
cd ${TRAVIS_BUILD_DIR}
git clone https://github.com/MTG/essentia.git
cd essentia
python3 ./waf configure --mode=release --with-python
python3 ./waf
python3 ./waf install


showinfo "Building the library..."
cd ${TRAVIS_BUILD_DIR}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_PYTHON3=ON -DUSE_LIBFFTW=ON -DBUILD_BENCHMARKS=ON -DBUILD_TESTS=ON -DBUILD_EXTENSIONS=ON -DBUILD_DOCS=OFF -DENABLE_DEBUG_INFORMATION=ON -DBUILD_EXAMPLES=ON -DENABLE_COVERAGE=ON ..
make -j8
make install
if [ $? -ne 0 ]; then
    error "Error: there are compile errors!"
    exit 3
fi

showinfo "Running the tests..."
cd ${TRAVIS_BUILD_DIR}
pip3 install --upgrade pip
pip3 install -U numpy
pip3 install -U scipy
pip3 install -U spectrum
pip3 install -U cython
pip3 install -U madmom
pip3 install git+https://github.com/sdrobert/pydrobert-speech.git#egg=pydrobert-speech
pip3 install eyed3 pydub pyaudioanalysis pytaglib pysndfile samplerate soundfile
pip3 install -r requirements.txt
python3 test/
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

showinfo "Success: All tests compile and pass."
