Simple Derivative Solver
================================================================================

[![Build Status](https://travis-ci.org/tsemaylo/DerrivativeSolver.svg?branch=master)](https://travis-ci.org/tsemaylo/DerrivativeSolver)

# What is it?

This is a small command line programm which calculates a derivative of given mathematical expression. 
Project is created solely to train C++ skills and pursues only academic purposes.
This should explain why I have to develope a wheal, instead of using a large variety of existing tools.

# How to use it?
First of all, you need to [build it](#build) before you can use it.

The usage is simple

DerivativeSolver <expression> <variable>

Couple of examples:
```
$ DerivativeSolver "2*x + x^2" x
$ 2 + 2*x
```

```
$ DerivativeSolver "a + b" x
$ 0
```

```
$ DerivativeSolver sin(x^2) x
$ cos(x^2)*2x
```
# Features

At the current state of development the following basic features are considered:
* Arythmetical operations: +, -, *, /, exponentiation (^)
* Basic elementary functions: natural logarithms, trygonometric functions (sine, cosine, tangent and co-tangent), exponent
* Command line interface

Nice to have options:
* LaTeX output
* Plot the graph of calculated functions. 

# Building and installing <a name="build"></a>

Assuming that you are already downloaded the source code to your PC and switched 
to a directory containig it using your favorite command shell.

The CMake build system is used to configure, build and install the application.
So make sure that you have installed the CMake on your PC.

The build procedure basically consists of the following steps:

```
$ mkdir build
$ cd build
$ cmake .. 
# alternatively you can specify the installation directory, for instance
# cmake .. -DCMAKE_INSTALL_PREFIX:PATH=/home/username/derivativesolver
$ make
$ make test # optional, can be used during debug and development
$ make install # installation may require super-user permissions
```

# Developing 

In the current state the application is not redy to use.
But don't worry only one class has to be implemented to be able to use the app.

The information regarding the design of application is available in [design notes](design/docs/notes.md).