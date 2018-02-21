/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultWithNumeratorRule.cpp
 * 
 * Implementation of the MultWithNumeratorRule class.
 * 
 * @author   agor
 * @since 21.01.2018
 */

#include "MultWithNumeratorRule.h"
#include <ExpressionFactory.h>

MultWithNumeratorRule::MultWithNumeratorRule(PMult _expression) : OptimizationRule(_expression) {
}

bool MultWithNumeratorRule::apply() throw(TraverseException) {
    bool largIsDiv=isTypeOf<Div>(this->expression->lArg);
    bool rargIsDiv=isTypeOf<Div>(this->expression->rArg);
    
    // either right or left arg of this multiplication must be Div - in this case the rule is applicable    
    
    if(largIsDiv && rargIsDiv){
        return false;
    }
    
    if(largIsDiv){
        PDiv castedDiv=SPointerCast<Div>(this->expression->lArg);
        this->optimizedExpression=createDiv(createMult(this->expression->rArg, castedDiv->lArg), castedDiv->rArg);
        return true;
    }
    
    if(rargIsDiv){
        PDiv castedDiv=SPointerCast<Div>(this->expression->rArg);
        this->optimizedExpression=createDiv(createMult(this->expression->lArg, castedDiv->lArg), castedDiv->rArg);
        return true;
    }
    
    return false;
}
