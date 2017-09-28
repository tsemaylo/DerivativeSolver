/**
 * @file SumWithNullArgumentRule.cpp
 * 
 * Implementation of optimization rule to remove zeroes from the arguments of summation
 * 
 * @author agor
 * @since 28.09.2017
 */

#include "SumWithNullArgumentRule.h"

#include <Constant.h>
#include <Sum.h>

SumWithNullArgumentRule::SumWithNullArgumentRule(PSum _expression) : OptimizationRule(_expression) {
}

bool SumWithNullArgumentRule::apply()  throw(TraverseException) {
    PSum typedExpression = SPointerCast<Sum>(this->expression);
    
    if(isTypeOf<Constant>(typedExpression->lArg) && SPointerCast<Constant>(typedExpression->lArg)->value=="0"){
        this->optimizedExpression=typedExpression->rArg;
        return true;
    }
    
    if(isTypeOf<Constant>(typedExpression->rArg) && SPointerCast<Constant>(typedExpression->rArg)->value=="0"){
        this->optimizedExpression=typedExpression->lArg;
        return true;
    }
            
    return false;
}

