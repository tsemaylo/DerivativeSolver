#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/derivativesolver -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++

make 
make test
make install

