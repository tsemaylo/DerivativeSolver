/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumWithNegativeRule.h
 * 
 * Definition of SumWithNegativeRule optimization rule.
 * 
 * @author agor
 * @since 11.02.2017
 */

#include "SumWithNegativeRule.h"

#include <ExpressionFactory.h>
#include "Doubles.h"

SumWithNegativeRule::SumWithNegativeRule(PSum _expression) : OptimizationRule(_expression){

}

bool ifMultIsANegation(PMult mult, std::function<bool(PExpression)> returnSub) {
    bool isLConst = isTypeOf<Constant>(mult->lArg);
    bool isRConst = isTypeOf<Constant>(mult->rArg);

    if(isLConst && isRConst){
        return false;
    }
    
    if(isLConst && isRConst){
        return false;
    }
    
    if(isLConst){
        PConstant c=SPointerCast<Constant>(mult->lArg);
        if(equal(c->value, -1.0)){
            return returnSub(mult->rArg);
        }
        return false;
    }
    
    PConstant c=SPointerCast<Constant>(mult->rArg);
        if(equal(c->value, -1.0)){
            return returnSub(mult->lArg);
        }
        return false;
}

bool SumWithNegativeRule::apply() throw(TraverseException) {
    // one argument of summation must be in the for -1*a
    bool largIsMult=isTypeOf<Mult>(this->expression->lArg);
    bool rargIsMult=isTypeOf<Mult>(this->expression->rArg);
    
    if(!largIsMult && !rargIsMult){
        return false;
    }
    
    // find out which argument is negated
    if(largIsMult){
        return ifMultIsANegation(SPointerCast<Mult>(this->expression->lArg), [this](PExpression subArg) -> bool {
            this->optimizedExpression=createSub(this->expression->rArg, subArg);
            return true;
        });
    }
    
    if(rargIsMult){
        return ifMultIsANegation(SPointerCast<Mult>(this->expression->rArg), [this](PExpression subArg) -> bool {
            this->optimizedExpression=createSub(this->expression->lArg, subArg);
            return true;
        });
    }
        
    return false;
}
