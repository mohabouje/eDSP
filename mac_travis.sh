#!/bin/bash

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m' # No Color
BG='\033[0;32m' # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
allert () { echo -e "${RED}$1${NC}"; }

showinfo "Building and installing extensions"
cd ${TRAVIS_BUILD_DIR} && cd extension
mkdir -p build && cd build
cmake .. && make -j8
sudo make install
cd .. && cd ..
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

showinfo "Building the library..."
cd ${TRAVIS_BUILD_DIR}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DUSE_LIBFFTW=ON -DBUILD_BENCHMARKS=ON -DBUILD_TESTS=ON -DBUILD_EXTENSIONS=ON -DBUILD_DOCS=OFF -DENABLE_DEBUG_INFORMATION=ON -DBUILD_EXAMPLES=ON -DENABLE_COVERAGE=ON ..
make -j8
sudo make install
if [ $? -ne 0 ]; then
    error "Error: there are compile errors!"
    exit 3
fi

showinfo "Running the tests..."
cd ${TRAVIS_BUILD_DIR}
sudo pip3 install --upgrade pip
sudo pip3 install -U numpy
sudo pip3 install -U scipy
sudo pip3 install -U spectrum
sudo python3 test/
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

showinfo "Success: All tests compile and pass."