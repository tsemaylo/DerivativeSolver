/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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

#include <string>

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
#include "Ctan.h"
#include "Ln.h"
#include "Exp.h"

PVariable createVariable(const std::string name);
PConstant createConstant(const double val);
/**
 * Create Constant from the string representation of nummeric value.
 * 
 * Can throw the invalid_argument or out_of_range.
 */
PConstant createConstant(const std::string strVal);
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
PExp createExp();
PExp createExp(PExpression arg);
PCos createCos();
PCos createCos(PExpression arg);
PSin createSin();
PSin createSin(PExpression arg);
PTan createTan();
PTan createTan(PExpression arg);
PCtan createCtan();
PCtan createCtan(PExpression arg);

#endif /* EXPRESSIONFACTORY_H */

