#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

# procedure to build a project
rm -Rf ./build #clean the build directory
mkdir build 
cd build 
#cmake .. -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser -DCMAKE_BUILD_TYPE=Debug -DCMAKE_CXX_COMPILER=g++
make 
make install
make test

