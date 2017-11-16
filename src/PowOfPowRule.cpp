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
    PPow typedExpr=SPointerCast<Pow>(this->expression);
    
    if(isTypeOf<Pow>(typedExpr->lArg)){
        PPow leftTerm=SPointerCast<Pow>(typedExpr->lArg);
        this->optimizedExpression=createPow(leftTerm->lArg, createMult(leftTerm->rArg, typedExpr->rArg));
        return true;
    }
    
    // try to match pattern 1/x^n
    
    if(!isTypeOf<Div>(typedExpr->lArg)){
        return false;
    }
    PDiv div=SPointerCast<Div>(typedExpr->lArg);
    
    if(!isTypeOf<Constant>(div->lArg)){
        return false;
    }
    
    if(SPointerCast<Constant>(div->lArg)->value != 1.0){
        return false;
    }

    if(isTypeOf<Variable>(div->rArg)){
        this->optimizedExpression=createPow(div->rArg, createMult(createConstant(-1.0), typedExpr->rArg));
        return true;
    }

    if(isTypeOf<Pow>(div->rArg)){
        PPow pow=SPointerCast<Pow>(div->rArg);
        this->optimizedExpression=createPow(pow->lArg, createMult(createConstant(-1.0), createMult(pow->rArg, typedExpr->rArg)));
        return true;
    }
    
    return false;
}
