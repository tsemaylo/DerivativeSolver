/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     PowOfPowRule.cpp
 * 
 * Implementation of the PowOfPowRule class.
 * 
 * @author   agor
 * @since 16.11.2017
 */

#include "PowOfPowRule.h"
#include <ExpressionFactory.h>

PowOfPowRule::PowOfPowRule(PPow _expression) : OptimizationRule(_expression) {
}


bool PowOfPowRule::apply() throw (TraverseException){
    if(isTypeOf<Pow>(this->expression->lArg)){
        PPow leftTerm=SPointerCast<Pow>(this->expression->lArg);
        this->optimizedExpression=createPow(leftTerm->lArg, createMult(leftTerm->rArg, this->expression->rArg));
        return true;
    }
    
    // try to match pattern 1/x^n
    
    if(!isTypeOf<Div>(this->expression->lArg)){
        return false;
    }
    PDiv div=SPointerCast<Div>(this->expression->lArg);
    
    if(!isTypeOf<Constant>(div->lArg)){
        return false;
    }
    
    if(SPointerCast<Constant>(div->lArg)->value != 1.0){
        return false;
    }

    if(isTypeOf<Variable>(div->rArg)){
        this->optimizedExpression=createPow(div->rArg, createMult(createConstant(-1.0), this->expression->rArg));
        return true;
    }

    if(isTypeOf<Pow>(div->rArg)){
        PPow pow=SPointerCast<Pow>(div->rArg);
        this->optimizedExpression=createPow(pow->lArg, createMult(createConstant(-1.0), createMult(pow->rArg, this->expression->rArg)));
        return true;
    }
    
    return false;
}
