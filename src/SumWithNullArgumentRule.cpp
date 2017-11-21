/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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
    if(isTypeOf<Constant>(this->expression->lArg) && SPointerCast<Constant>(this->expression->lArg)->value==0.0){
        this->optimizedExpression=this->expression->rArg;
        return true;
    }
    
    if(isTypeOf<Constant>(this->expression->rArg) && SPointerCast<Constant>(this->expression->rArg)->value==0.0){
        this->optimizedExpression=this->expression->lArg;
        return true;
    }
            
    return false;
}

