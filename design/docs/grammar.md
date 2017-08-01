The basic grammar of math expressions for parser.

The order of rule application defines the priority of opperation.

1.	'a..Z'				-> Variable
2.	'0..1' Constant		-> Constant
3.	'('					-> BracketO
4.	')'					-> BracketC
5.	Variable			-> CompleteExpr
6.	Constant			-> CompleteExpr 
7.	Sum					-> CompleteExpr
8.	Sub					-> CompleteExpr
9.	Mult				-> CompleteExpr
10.	Div					-> CompleteExpr
11.	Pow					-> CompleteExpr
12.	Function			-> CompleteExpr 
13.	'sin'				-> IncompleteFunc
14.	'cos'				-> IncompleteFunc
15.	'tan'				-> IncompleteFunc
16.	'ctan'				-> IncompleteFunc
17.	'ln'				-> IncompleteFunc
18.	'exp'				-> IncompleteFunc
19.	BracketO CompleteExpr BracketC	-> CompleteExpr
20.	IncompletFunc CompleteExpr		-> Function
21.	CompleteExpr '^'				-> PowL
22.	PowL CompleteExpr				-> Pow
23.	CompleteExpr '*'				-> MultL
24.	MultL CompleteExpr				-> Mult
25.	CompleteExpr '/'				-> DivL
26.	DivL CompleteExpr				-> Div
27.	CompleteExpr '+'				-> SumL
28.	SumL CompleteExpr				-> Sum
29.	CompleteExpr '-'				-> SubL
30.	SubL CompleteExpr				-> Sub
