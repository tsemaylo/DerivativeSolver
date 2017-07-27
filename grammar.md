The basic grammar of math expressions for parser.

The order of rule application defines the priorita of opperation.

'a..Z'				-> Variable
'0..1' Constant		-> Constant
'('					-> BracketO
')'					-> BracketC
Variable			-> CompleteExpr
Constant			-> CompleteExpr
Sum					-> CompleteExpr
Sub					-> CompleteExpr
Mult				-> CompleteExpr
Div					-> CompleteExpr
Pow					-> CompleteExpr
Function			-> CompleteExpr 
'sin'				-> IncompleteFunc
'cos'				-> IncompleteFunc
'tan'				-> IncompleteFunc
'ctan'				-> IncompleteFunc
'ln'				-> IncompleteFunc
'exp'				-> IncompleteFunc
BracketO CompleteExpr BracketC	-> CompleteExpr
IncompletFunc CompleteExpr		-> Function
CompleteExpr '^'				-> PowL
PowL CompleteExpr				-> Pow
CompleteExpr '*'				-> MultL
MultL CompleteExpr				-> Mult
CompleteExpr '/'				-> DivL
DivL CompleteExpr				-> Div
CompleteExpr '+'				-> SumL
SumL CompleteExpr				-> Sum
CompleteExpr '-'				-> SubL
SubL CompleteExpr				-> Sub
