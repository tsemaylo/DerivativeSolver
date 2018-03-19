#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

export CXX="g++"
export CC="gcc"

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 

VALGRIND_FLAG="Off"
if [ "$DO_VALGRIND_TEST" = "1" ]; then
    VALGRIND_FLAG="On"
fi

cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/derivativesolver -DCMAKE_BUILD_TYPE=Debug -DDO_VALGRIND_TEST=$VALGRIND_FLAG -DDO_TESTING=On

make 
make test
make install

cd ..

if [ "$CXX" = "g++" ]; then 
    ./lcov.sh
fi

if [ "${DO_CODE_ANALYSIS}" = "1" ]; then
    ./cppcheck.sh
fi