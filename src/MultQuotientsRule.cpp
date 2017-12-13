/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultQuotientsRule.cpp
 * 
 * Definition of the MultQuotientsRule class.
 * 
 * @author   agor
 * @since 13.12.2017
 */

#include "MultQuotientsRule.h"
#include <ExpressionFactory.h>

MultQuotientsRule::MultQuotientsRule(PMult _expression) : OptimizationRule(_expression) {
}

bool putConstantToLeft(PMult expr, std::function<bool (PMult)> onSuccess) {
    bool isLArgConst = isTypeOf<Constant>(expr->lArg);
    bool isRArgConst = isTypeOf<Constant>(expr->rArg);
    
    if(!isLArgConst && !isRArgConst){
        return false;
    }
    
    // try to put constants of the left side
    if(isRArgConst) {
        return onSuccess(createMult(expr->rArg, expr->lArg));
    } else {
        return onSuccess(createMult(expr->lArg, expr->rArg));
    }
    return true;
}

bool MultQuotientsRule::apply() throw(TraverseException) {
    return putConstantToLeft(this->expression, [this](PMult normalizedOuterMult) -> bool {
        PMult innerMult;
        if(isTypeOf<Div>(normalizedOuterMult->rArg)) {
            PDiv innerDiv=SPointerCast<Div>(normalizedOuterMult->rArg);
            innerMult=createMult(innerDiv->lArg, createDiv(createConstant(1.0), innerDiv->rArg));
        } else if(isTypeOf<Mult>(normalizedOuterMult->rArg)) {
            innerMult=SPointerCast<Mult>(normalizedOuterMult->rArg);
        } else {
            return false;
        }
        
        return putConstantToLeft(innerMult, [&normalizedOuterMult, this](PMult normalizedInnerMult) -> bool {
            PConstant c1 = SPointerCast<Constant>(normalizedOuterMult->lArg);
            PConstant c2 = SPointerCast<Constant>(normalizedInnerMult->lArg);
            double newQuot = c1->value * c2->value;
            this->optimizedExpression=createMult(createConstant(newQuot), normalizedInnerMult->rArg);
            return true;
        });
    });
}
