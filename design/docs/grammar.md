The basic grammar of math expressions for parser.

The order of rule application defines the priority of opperation.

No.	|Stack pattern					| Reduced to	| Implmented in | Additional notes
----|-------------------------------|---------------|---------------|------------------
1	|'a..Z'							| Variable		| 'Shift' operation in **Parser** | 
2	|'0..1'							| Constant		| s.a. | 
3	|'('							| BracketO		| s.a. | Should a new Expression type **Bracket** be introduced? How opening and closing brackets can be distincted?
4	|')'							| BracketC		| s.a. | 
5   |'+'							| SumE			| s.a. | SumE is represented by Sum object without arguments. The same is appliable for all non-terminals with notation *E |
6   |'-'							| SubE			| s.a. | 
7   |'*'							| MultE			| s.a. | 
8   |'/'							| DivE			| s.a. | 
9   |'^'							| PowE			| s.a. | 
10	|'sin'							| SinE			| s.a. | 
11	|'cos'							| CosE			| s.a. | 
12	|'tan'							| TanE			| s.a. | 
13	|'ctan'							| CtanE			| s.a. | 
14	|'ln'							| LnE			| s.a. | 
15	|'exp'							| ExpE			| s.a. | 
16	|Variable \|<br> Constant	\|<br> Sum \|<br> Sub \|<br> Mulz \|<br> Div \|<br> Pow \|<br> Sin \|<br> Cos \|<br> Tan \|<br> Ctan \|<br> Ln \|<br> Exp | CompleteExpr	| N.A. | CompleteExpr represents the final form of **Expression** object which can't be clarified, for example function with completely asigned arguument, aperations with both initialized arguments and so on. **Variable**s and **Constant**s are anitially considered as completed. Any operation type expression has both arguments initialized, then it can be considered as 'completed'.
18	|BracketO CompleteExpr BracketC	| CompleteExpr	| Reduced by **RuleBracket**  | 
19	|SinE CompleteExpr				| Sin			| Reduced by **RuleFunction** | Application of function f to the argument x considers usage brackets: f(x) but not fx.
20	|CosE CompleteExpr				| Cos			| Reduced by **RuleFunction** | 
21	|TanE CompleteExpr				| tan			| Reduced by **RuleFunction** | 
22	|CtanE CompleteExpr				| Ctan			| Reduced by **RuleFunction** | 
23	|LnE CompleteExpr				| Ln			| Reduced by **RuleFunction** | 
24	|ExpE CompleteExpr				| Exp			| Reduced by **RuleFunction** | 
25	|CompleteExpr PowE				| PowL			| Reduced by **RulePowLV** | 
26	|PowL CompleteExpr				| Pow			| Reduced by **RulePowRV** | 
27	|CompleteExpr MultE				| MultL			| Reduced by **RuleMultLV** | 
28	|MultL CompleteExpr				| Mult			| Reduced by **RuleMultRV** | 
29	|CompleteExpr DivE				| DivL			| Reduced by **RuleDivLV** | 
30	|DivL CompleteExpr				| Div			| Reduced by **RuleDivRV** | 
31	|CompleteExpr SumE				| SumL			| Reduced by **RuleSumLV** | 
32	|SumL CompleteExpr				| Sum			| Reduced by **RuleSumRV** | 
33  |SumE CompleteExpr				| CompleteExpr	| Reduced by **RuleSumRV** | Sum: (NULL, ComleteExpr) -> CompleteExpt . Examples  +5=5; +six(x)=sin(x); sin(+x)=sin(x) 
34	|CompleteExpr SubE				| SubL			| Reduced by **RuleSubLV** | 
35	|SubL CompleteExpr				| Sub			| Reduced by **RuleSubRV** | 
36  |SubE CompleteExpr				| Mult			| Reduced by **RuleSubRV** | Mult: (-1, CompleteExpr) 
