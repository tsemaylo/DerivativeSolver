# Design notes

## Overview
Basically the application consists of the following basic elements:

* **Parser** - accepts string expression and builds syntax tree
* **Syntax tree** - the hierarchical data structure representing the parsed expression. 
* **Visitors** are tools to perform operations over syntax tree: like differentiation or output in user-readable form.

## Design goals and priorities
- Taste of c++ and get the experience with actual standards
- Keep design as clean as possible

## Basic considerations

* using c++14
* gcc + plain Makefiles
* smart pointers instead of explicit memory management.
* keep syntax tree element as simple as possible, PODs would be great
* -Wall -Werror -Wpedantic
* minimize inheretance, nevertheless it can be essential to use polymorphism in some way.
* exceptions instead of error codes

## Design of the application

The design, as it usually happens, is evolving during the development. 
The initial model of the application are preserved here: [Initial design](initialDesign.md)
Here you can find the actual structure of the application. The basic elements of design, as it was
mentioned above, are: parser, syntax tree and visitors as abstraction for operations.

The relationships between these items and basic decomposition is provided on the picture below.

![General decomposition](img/designItemsRelationships.png)

It is, for sure, a very coarse representation of the application structure. 

The relationship "uses" represents the point where the "breakable" dependency between items appear. 
Making a sophisticated design as application grows may consider a usage of "serious" dependency 
breaking techniques, say IoC, to improve testability and modulatization. 

The more detailed class decomposition looks as following:
![Class diagram](img/generalStructure.png)

The **Parser** implement parsing logic and operates with a grammar. The grammar is built of 
**Rule**s which are implementing certain [grammar rules](grammar.md). The parser implements the 
"Shift-Reduce" method, at least some sort of it, because of simplicity of implementation. 
With this approach the high performance can't be anticipateda and it is not a priority so far.  

The digram below illustrates the "Parser <-> Rule" relationships and the structure of 
rules based on the [grammar description](grammar.md).

![Parser-Rule](img/parserRule.png)

"Syntax tree" is a data structure which represents the parsed expression. 
It has **Expression** as a base class and the following element are representing
syntax tree items.

![Class diagram](img/syntaxTree.png)

We also have **Application** object which handles interaction with user, provides entry point and performs error handling.

### Exception handling

Since no complex execution logic or sophisticated recovery after errors are considered, 
it is decided to to error handling on the level of **Application**.

The only one reasonable error handling here is just printing an error information to the user,
and this is the responsibility of **Application**.

## Testing
Two types of testing are considered:

**Unit testing**

There are some test cases maintained during development. 
Say ``` make clean all ``` and available tests will be run automatically during the build process.
The project incorporates [Google's C++ Test Framework](https://github.com/google/googletest "Google Test").
The naming of test cases is based on these ["Naming standards for unit tests"](http://osherove.com/blog/2005/4/3/naming-standards-for-unit-tests.html).

**Acceptance tests**

Represented as an automated script which performs testing of application against most relevant input data.
Performed in the build time.

## What TO-be-DOne
- [x] Basic design
- [x] Implement basic design elements in code
- [x] Clarifying and verifying the grammar 
- [x] Identify rules to be implemented
- [x] Implementation of Parser <br/>
      Implementation of rules
- [x] RuleSumLV 
- [x] RuleSumRV
- [x] RuleSubLV 
- [x] RuleSubRV 
- [x] RuleMultLV 
- [x] RuleMultRV 
- [x] Refactoring of **Rule**s and **Parser** 
- [x] RuleDivLV
- [x] RuleDivRV
- [x] RulePowLV 
- [x] RulePowRV 
- [x] RuleFunction 
- [ ] Rule for multiplication without sign of multiplication<br>
      Parsing Improvement 
- [ ] Being case-irrelevant
- [ ] Support floating point numbers <br><br>
- [x] Update design docs 
  - [x] also describe how to name test cases
- [ ] Implementation of Differentiator  (IN PROGRESS)
- [x] Implementation of StringGenerator
- [ ] Implement visitor to simplify the expression 
- [ ] Review of the design 
- [ ] Remove redundant unit test cases from ParserTest
- [ ] Test runs with Valgrind
- [ ] Testing scripts for whole application
- [ ] Check testing coverage 