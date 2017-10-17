#!/bin/sh

# procedure to build a project

mkdir build 
cd build 
cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/tmp/testlibagmathparser 
make 
make install
make test
