#!/bin/bash

RED='\033[0;31m' # Red
BB='\033[0;34m'  # Blue
NC='\033[0m' # No Color
BG='\033[0;32m' # Green

error() { >&2 echo -e "${RED}$1${NC}"; }
showinfo() { echo -e "${BG}$1${NC}"; }
workingprocess() { echo -e "${BB}$1${NC}"; }
allert () { echo -e "${RED}$1${NC}"; }


showinfo "Starting the process"
cd ${TRAVIS_BUILD_DIR}
lcov --capture --initial --directory . --output-file header-only.info --no-external

showinfo "1 - Building the library."
mkdir -p build
cd build
cmake -DCMAKE_BUILD_TYPE=Debug -DBUILD_TESTS=ON -DBUILD_DOCS=OFF -DENABLE_DEBUG_INFORMATION=ON ..
make -j8
if [ $? -ne 0 ]; then
    error "Error: there are compile errors!"
    exit 3
fi

showinfo "2 - Test & Code Coverage"
workingprocess "Running the test..."
make test
if [ $? -ne 0 ]; then
    error "Error: there are some tests that failed!"
    exit 4
fi

workingprocess "Generating the test-only code coverage..."
cd ${TRAVIS_BUILD_DIR}
lcov --capture --directory . --ouput-file test-only.info
lcov --add-tracefile header-only.info --add-tracefile test-onle.info --output-file coverage.info
lcov --remove coverage.info '/usr/*' --output-file coverage.info

workingprocess "Displaying the final results..."
lcov --list coverage.info

showinfo "Success: All tests compile and pass."