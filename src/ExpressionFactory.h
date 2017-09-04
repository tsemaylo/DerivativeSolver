/**
 * @file ExpressionFactory.h
 * 
 * Definition of factory functions for expression elements.
 * 
 * @author agor
 * @since 04.09.2017
 */

#ifndef EXPRESSIONFACTORY_H
#define EXPRESSIONFACTORY_H

#include "Variable.h"
#include "Constant.h"
#include "Sum.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"
#include "Pow.h"
#include "Sin.h"
#include "Cos.h"
#include "Tan.h"
#include "Ln.h"


PVariable createVariable(const string name);
PConstant createConstant(const string val);
PSum createSum();
PSum createSum(PExpression lArg, PExpression rArg);
PSub createSub();
PSub createSub(PExpression lArg, PExpression rArg);
PMult createMult();
PMult createMult(PExpression lArg, PExpression rArg);
PDiv createDiv();
PDiv createDiv(PExpression lArg, PExpression rArg);
PPow createPow();
PPow createPow(PExpression lArg, PExpression rArg);
PLn createLn();
PLn createLn(PExpression arg);
PCos createCos(PExpression arg);
PSin createSin(PExpression arg);
PTan createTan(PExpression arg);

#endif /* EXPRESSIONFACTORY_H */

