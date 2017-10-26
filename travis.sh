#!/bin/sh

set -e 

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. 
make 
make test
