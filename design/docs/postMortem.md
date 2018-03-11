Design review / post mortem
============================================

This page represents short summary of code/design review.
It lists major design flaws and elaborates the possible improvements.

**(1)** The first and the most significant design problem is constructed by the way the
syntax tree is processed. For sure, the concept of Visitor pattern allows us to
use polymorphism as an instrument to traverse the tree of Expressions without
nasty type casting when we handling the single node of the tree. But from the
other side it doesn't preserve the context if we need to *dig into* the current node
and *rebuild it* using some smart heuristics. In this case the syntax tree node is
an object of a generic type Expression. Therefore there is no way to know which
exactly type of Expression was provided. It is the reason why such kind of
awkward workarounds like isTypeOf<>() and SPointerCast<>() are existing. The problem
is clearly brought to the light in optimization rules, which are bloated with isTypeOf's
conditions making the reasoning about the code hard.


**(2)** Simplification of an Expression requires more intelligent approach rather then
just hardcoded heuristics represented by OptimizationRule. Additional support from
the language, like **pattern matching**, could reduce programming efforts. But it
will not solve the problem completely and flexibly. It will just make life easier
for programmer.

Sort of neural network can be an option. But this topic is interesting by itself
and deserves to be elaborated aside from this project.

**(3)** Usage of smart pointers is obviously a nice idea.
Especially if the syntax tree must be reorganized and existing nodes reused, the
reference counting provided in shared_ptr and corresponding memory management
present huge benefits.

BUT, it virtually destroys the inheritance that makes life difficult.
The overuse of inheritance that is also a case here and it is clearly a design flaw.

**(4)** The lack of encapsulation for token types in parser.

It causes a duplication of conditions based on token type. Adding a new token
type later requires additional efforts constituted by changing several places in
code and implementing proper error handling. As an alternative a some kind of
"selector" based on lambdas can be used.