The basic grammar of math expressions for parser.

The order of rule application defines the priority of opperation.

No.	|Stack pattern					| Reduced to		| Implmented in | Additional notes
----|-------------------------------|-------------------|---------------|------------------
1	|'a..Z'							| Variable			| 'Shift' operation in **Parser** | 
2	|'0..1'							| Constant			| s.a. | 
3	|'('							| BracketO			| s.a.  | Should a new Expression type **Bracket** be introduced? How opening and closing brackets can be distincted?
4	|')'							| BracketC			| s.a.  | 
5   |'+'							| SumE			| s.a. SumE is represented by Sum object without arguments. The same is appliable for all non-terminals with notation *E |
6   |'-'							| SubE			| s.a. | 
7   |'*'							| MultE			| s.a. | 
8   |'/'							| DivE			| s.a. | 
9   |'^'							| PowE			| s.a. | 
10	|Variable						| CompleteExpr			| N.A. | CompleteExpr represents the final form of **Expression** object which can't be clarified, for example function with completely asigned arguument, aperations with both initialized arguments and so on. **Variable**s and **Constant**s are anitially considered as completed.
11	|Constant						| CompleteExpr			| N.A. | 
12	|Sum							| CompleteExpr			| N.A. | Any operation type expression has both arguments initialized, then it can be considered as 'completed'.
13	|Sub							| CompleteExpr			| N.A. | 
14	|Mult							| CompleteExpr			| N.A. | 
15	|Div							| CompleteExpr			| N.A. | 
16	|Pow							| CompleteExpr			| N.A. | 
17	|Function						| CompleteExpr			| N.A. | 
18	|'sin'							| SinE					| 'Shift' opeartion in **Parser** | 
19	|'cos'							| CosE		| s.a. | 
20	|'tan'							| TanE		| s.a. | 
21	|'ctan'							| CtanE		| s.a. | 
22	|'ln'							| LnE		| s.a. | 
23	|'exp'							| ExpE		| s.a. | 

24	|BracketO CompleteExpr BracketC	| CompleteExpr			| TBD | 
25	|IncompletFunc CompleteExpr		| Function				| Reduced by **RuleFunction** | Application of function f to the argument x considers usage brackets: f(x) but not fx.
26	|CompleteExpr PowE				| PowL			| Reduced by **RulePowLV** | 
27	|PowL CompleteExpr				| Pow			| Reduced by **RulePowRV** | 
28	|CompleteExpr MultE				| MultL			| Reduced by **RuleMultLV** | 
29	|MultL CompleteExpr				| Mult			| Reduced by **RuleMultRV** | 
30	|CompleteExpr DivE				| DivL			| Reduced by **RuleDivLV** | 
31	|DivL CompleteExpr				| Div			| Reduced by **RuleDivRV** | 
32	|CompleteExpr SumE				| SumL			| Reduced by **RuleSumLV** | 
33	|SumL CompleteExpr				| Sum			| Reduced by **RuleSumRV** | 
34  |SumE CompleteExpr				| CompleteExpr	| Reduced by **RuleSumRV** | Z.b +5; +six(x); sin(+x) 
35	|CompleteExpr SubE				| SubL			| Reduced by **RuleSubLV** | 
36	|SubL CompleteExpr				| Sub			| Reduced by **RuleSubRV** | 
37  |SubE CompleteExpr				| Mult			| Reduced by **RuleSubRV** | Mult: (-1, CompleteExpr) 
