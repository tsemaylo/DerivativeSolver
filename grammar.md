Some sketches of expected expression grammar.

Basic considerations and definitions.
Non-terminals will be denoted by symbol '#' in the identifier.
Like #A, #B, #JOE, #MARY 
Terminals are normal alphanummerical symbols ar whatever is relevant to depict math expression.
| - means multiple alternatives "A | B" is equal to "A" or "B"

Lets start from basic arithmetic
```
#E -> #LV #OP #RV 
#E -> ( #E )
#OP ->  +
      | -
      | *
      | /
#RV -> #LV
```
Operands can be either alphanumerical constants or variables, functions or other expressions
```
#LV -> #A | #N | #F | #E
#LV -> ( #LV )
#A -> a...Z
#I -> 0...9
#N -> #I.#I | #I
#N -> -#N
#F -> sin(#E) | cos(#E)
```