#!/bin/sh

set -e 

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug
cat src/MathParser/build/CMakeFiles/libagmathparser.dir/flags.make 
make 
make test


if [ "${DO_CODE_ANALYSIS}" = "1" ]; then
    # do code check (not the best place for it, but it works)
    cd ..
    ./cppcheck.sh
fi