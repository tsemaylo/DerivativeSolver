Simple Derivative Solver
================================================================================

[![Build Status](https://travis-ci.org/tsemaylo/DerivativeSolver.svg?branch=master)](https://travis-ci.org/tsemaylo/DerivativeSolver)
[![codecov](https://codecov.io/gh/tsemaylo/DerivativeSolver/branch/master/graph/badge.svg)](https://codecov.io/gh/tsemaylo/DerivativeSolver)


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

## Expression syntax

Nummerical constants: 1, 2, 4.2

Variables: any sequence of aplha characters. For example: a, b, var

Arithmetic operations: 

 Opeartion     | Symbol | Example
---------------|--------|---------
Addition       | +      | a + b
Subtraction    | -      | x + 1
Multiplication | *      | a*b <br> 2a <br> 3sin(x)
Division       | /      | a/b
Exponentiation | ^      | a^2 <br> x^y <br> (sin(x))^2

Functions: 

 Function                 | Symbol | Example
--------------------------|--------|---------
Sine                      | sin    | sin(x)
Cosine                    | cos    | cos(x)
Tangent                   | tan    | tan(x)
Co-tangent                | ctan   | ctan(x)
Natural logarithm         | ln     | ln(x)
Exponential function, e^x | exp    | exp(x)

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
$ make install # installation may require super-user permissions
```

# Contribute 

The information regarding the design of application is available in [design notes](design/docs/notes.md).