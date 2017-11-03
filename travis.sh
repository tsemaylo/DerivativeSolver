#!/bin/sh

set -e 

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug
make 
make test

# do code check (not the best plyce for it, but it works)
cd ..
./cppcheck.sh