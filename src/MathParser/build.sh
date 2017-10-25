#!/bin/sh

# procedure to build a project
rm -Rf ./build #clean the build directory
mkdir build 
cd build 
#cmake .. -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
make 
make install
make test
