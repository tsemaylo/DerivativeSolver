#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

export CXX="g++"
export CC="gcc"

# procedure to build a project
rm -Rf ./build #clean the build directory
mkdir build 
cd build 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser -DCMAKE_BUILD_TYPE=Debug
make 
make install
make test

cd ..

if [ "$CXX" = "g++" ]; then 
    ./lcov.sh
fi
