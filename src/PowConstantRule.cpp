/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     PowConstantRule.h
 * 
 * Definition of the PowConstantRule class.
 * 
 * @author   agor
 * @since 16.11.2017
 */

#include "PowConstantRule.h"
#include <cmath>
#include <ExpressionFactory.h>
#include <Constant.h>

PowConstantRule::PowConstantRule(PPow _expression) : OptimizationRule(_expression){
}

bool PowConstantRule::apply() throw(TraverseException){
    PPow typedExpr=SPointerCast<Pow>(this->expression);
    
    if(!isTypeOf<Constant>(typedExpr->rArg)){
        return false;
    }
    
    PConstant exponent=SPointerCast<Constant>(typedExpr->rArg);
    if(exponent->value==0.0){
        this->optimizedExpression=createConstant(1.0);
        return true;
    }
    
    if(exponent->value==1.0){
        this->optimizedExpression=typedExpr->lArg;
        return true;
    }
    
    if(isTypeOf<Constant>(typedExpr->lArg)){
        PConstant base=SPointerCast<Constant>(typedExpr->lArg);
        this->optimizedExpression=createConstant(std::pow(base->value, exponent->value));
        return true;
    }
    
    return false;
}


