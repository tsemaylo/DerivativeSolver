#!/bin/sh

# small script to build everything from scratch
# used during development

set -e 

# procedure to build a project
rm -Rf ./build #clean the build directory
mkdir build 
cd build 
#cmake .. -G "Unix Makefiles" -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
make 
make install
make test
