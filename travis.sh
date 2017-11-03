#!/bin/sh

set -e 

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
make 
make test
