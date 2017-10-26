#!/bin/sh

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/derivativesolver 
make 
make test
make install

