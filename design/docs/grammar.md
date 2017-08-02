The basic grammar of math expressions for parser.

The order of rule application defines the priority of opperation.

No.	|Stack pattern					| Reduced to		| Implmented in | Additional notes
----|-------------------------------|-------------------|---------------|---------
1.	|'a..Z'							| Variable			| 'Shift' operation in **Parser** |
2.	|'0..1' Constant				| Constant			| s.a. |
3.	|'('							| BracketO			| s.a.  | Should a new Expression type **Bracket** be introduced? How opening and closing brackets can be distincted?
4.	|')'							| BracketC			| s.a.  |
TBD |'+'							| SumE			| s.a. SumE is represented by Sum object without arguments. The same is appliable for all non-terminals with notation *E |
TBD |'-'							| SubE			| s.a. |
TBD |'*'							| MultE			| s.a. |
TBD |'/'							| DivE			| s.a. |
TBD |'^'							| PowE			| s.a. |
5.	|Variable						| CompleteExpr			| N.A. | 
6.	|Constant						| CompleteExpr			| N.A. |
7.	|Sum							| CompleteExpr			| N.A. | Any operation type expression has both arguments initialized, then it can be considered as 'completed'.
8.	|Sub							| CompleteExpr			| N.A. |
9.	|Mult							| CompleteExpr			| N.A. |
10.	|Div							| CompleteExpr			| N.A. |
11.	|Pow							| CompleteExpr			| N.A. |
12.	|Function						| CompleteExpr			| ? |
13.	|'sin'							| IncompleteFunc		| 'Shift' opeartion in **Parser** |
14.	|'cos'							| IncompleteFunc		| s.a. |
15.	|'tan'							| IncompleteFunc		| s.a. |
16.	|'ctan'							| IncompleteFunc		| s.a. |
17.	|'ln'							| IncompleteFunc		| s.a. |
18.	|'exp'							| IncompleteFunc		| s.a. |
19.	|BracketO CompleteExpr BracketC	| CompleteExpr			||
20.	|IncompletFunc CompleteExpr		| Function				| Reduced by **RuleFunction** |
21.	|CompleteExpr PowE				| PowL			| Reduced by **RulePowLV** |
22.	|PowL CompleteExpr				| Pow			| Reduced by **RulePowRV** |
23.	|CompleteExpr MultE				| MultL			| Reduced by **RuleMultLV** |
24.	|MultL CompleteExpr				| Mult			| Reduced by **RuleMultRV** |
25.	|CompleteExpr DivE				| DivL			| Reduced by **RuleDivLV** |
26.	|DivL CompleteExpr				| Div			| Reduced by **RuleDivRV** |
27.	|CompleteExpr SumE				| SumL			| Reduced by **RuleSumLV** |
28.	|SumL CompleteExpr				| Sum			| Reduced by **RuleSumRV** |
TBD |SumE CompleteExpr				| CompleteExpr	| Reduced by **RuleSumRV** | Z.b +5; +six(x); sin(+x)
29.	|CompleteExpr SubE				| SubL			| Reduced by **RuleSubLV** |
30.	|SubL CompleteExpr				| Sub			| Reduced by **RuleSubRV** |
TBD |SubE CompleteExpr				| Mult			| Reduced by **RuleSubRV** | Mult: (-1, CompleteExpr)
