#!/bin/bash

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m' # No Color
BG='\033[0;32m' # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
allert () { echo -e "${RED}$1${NC}"; }

showinfo "Installing the deprecated package of boost numpy boost numpy"
cd ${TRAVIS_BUILD_DIR} && cd ..
git clone https://github.com/ndarray/Boost.NumPy.git
cd Boost.NumPy
mkdir -p build
cd build
cmake .. -DCMAKE_BUILD_TYPE=RELEASE
make -j6 && sudo make install
sudo mv /usr/local/lib64/libboost_numpy.so /usr/local/lib/

showinfo "Exporting libraries path..."
export LD_LIBRARY_PATH=${LD_LIBRARY_PATH}:/usr/local/lib64:/usr/local/lib

showinfo "Installing third-party tools"
pip install -U ipython numpy matplotlib pyyaml
cd ${TRAVIS_BUILD_DIR}
git clone https://github.com/MTG/essentia.git
cd essentia
sudo ./waf configure --mode=release --with-python
sudo ./waf
sudo ./waf install

showinfo "Building the library..."
cd ${TRAVIS_BUILD_DIR}
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Release -DUSE_BOOST_NUMPY_DEPRECATED=ON -DUSE_PYTHON3=OFF -DUSE_LIBFFTW=ON  -DBUILD_EXTENSIONS=ON -DBUILD_DOCS=OFF -DENABLE_DEBUG_INFORMATION=ON -DBUILD_EXAMPLES=ON ..
make -j8
sudo make install
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

sudo ldconfig

showinfo "Running the tests..."
cd ${TRAVIS_BUILD_DIR}
chmod -R ugo+rX /lib/python2.7/site-packages/
pip install --upgrade pip
pip install -U numpy
pip install -U scipy
pip install -U spectrum
pip install -U cython
pip install -U madmom
pip install git+https://github.com/sdrobert/pydrobert-speech.git#egg=pydrobert-speech
pip install librosa
python test/
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

showinfo "Success: All tests compile and pass."