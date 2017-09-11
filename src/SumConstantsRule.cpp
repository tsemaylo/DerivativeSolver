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
        double lArgVal = 0.0;
        double rArgVal = 0.0;
        try {
            lArgVal = std::stod(SPointerCast<Constant>(typedExpression->lArg)->value);
            rArgVal = std::stod(SPointerCast<Constant>(typedExpression->rArg)->value);

            std::stringstream strStream;
            strStream << std::fixed << std::setprecision(2) << (lArgVal + rArgVal);
            PConstant result = createConstant(strStream.str());
            this->optimizedExpression = result;
            return true;
        }
        catch (std::exception ex) {
            // re-throw an exception
            THROW(TraverseException, ex.what(), "N.A.");
        }
    }

    return false;
}