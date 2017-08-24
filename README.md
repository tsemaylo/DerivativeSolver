# What is it?

This is a small command line programm which calculates a derivative of given mathematical expression. 
Project is created solely to train C++ skills and pursues only academic purposes.
This should explain why I have to develope a wheal, instead of using a large variety of existing tools.

# How to use it?
First of all, you need to [buid it](#build) before you can use it.

The usage is simple

solver <expression> <variable>

Couple of examples:
```
$ solver "2*x + x^2" x
$ 2 + 2*x
```

```
$ solver "a + b" x
$ 0
```

```
$ solver sin(x^2) x
$ cos(x^2)*2x
```
# Features

At the current state of development the following basic features are available:
* Arythmetical operations: +, -, *, /, exponentiation (^)
* Basic elementary functions: natural logarithms, trygonometric functions (sine, cosine, tangent and co-tangent), exponent
* Command line interface

Nice to have options:
* LaTeX output
* Plot the graph of calculated functions. 

# Building <a name="build"></a>

The build procedure is standard :
make clean all test

# Developing 
The information regarding the design of application is available in [design notes](design/docs/notes.md).

