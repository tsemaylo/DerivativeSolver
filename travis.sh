#!/bin/sh

set -e 

VALGRIND_FLAG="Off"
if [ "$DO_VALGRIND_TEST" = "1" ]; then
    VALGRIND_FLAG="On"
fi

# reset the build directory
rm -Rf ./build 
mkdir -p build

cd build 
cmake .. -DCMAKE_BUILD_TYPE=Debug -DDO_VALGRIND_TEST=$VALGRIND_FLAG -DDO_TESTING=On
make 
make test


if [ "${DO_CODE_ANALYSIS}" = "1" ]; then
    # do code check (not the best place for it, but it works)
    cd ..
    ./cppcheck.sh
fi
