/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    SumConstantsRule.cpp
 * 
 * Implmentation of the SumConstantsRule.
 * 
 * @author   agor
 * @since 11.09.2017
 */

#include "SumConstantsRule.h"
#include <ios>
#include <iomanip>
#include <sstream>
#include <Expression.h>
#include <Sum.h>
#include <Constant.h>
#include <ExpressionFactory.h>
#include "ExceptionThrower.h"

SumConstantsRule::SumConstantsRule(PSum _expression) : OptimizationRule(_expression) {
}

bool SumConstantsRule::apply() throw (TraverseException) {
    PSum typedExpression = SPointerCast<Sum>(this->expression);
    // constant and constand - perform summation and return constant
    if (isTypeOf<Constant>(typedExpression->lArg) && isTypeOf<Constant>(typedExpression->rArg)) {
        double lArgVal = SPointerCast<Constant>(typedExpression->lArg)->value;
        double rArgVal = SPointerCast<Constant>(typedExpression->rArg)->value;

        this->optimizedExpression = createConstant(lArgVal + rArgVal);
        return true;
    }

    return false;
}