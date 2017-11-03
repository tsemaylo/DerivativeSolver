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
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/derivativesolver -DCMAKE_BUILD_TYPE=Debug

make 
make test
make install

cd ..

if [ "$CXX" = "g++" ]; then 
    ./lcov.sh
fi

export CPPCHECK_HOME="/opt/cppcheck/"
./cppcheck.sh