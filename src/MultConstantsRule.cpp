/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultConstantsRule.cpp
 * 
 * Implementation of the  MultConstantsRule class.
 * 
 * @author   agor
 * @since 11.09.2017
 */

#include "MultConstantsRule.h"
#include <Constant.h>
#include <ExpressionFactory.h>

MultConstantsRule::MultConstantsRule(PMult _expression) : OptimizationRule(_expression) {
}

bool MultConstantsRule::apply() throw(TraverseException) {
    if(isTypeOf<Constant>(this->expression->lArg) && isTypeOf<Constant>(this->expression->rArg)){
        double val1=SPointerCast<Constant>(this->expression->lArg)->value;
        double val2=SPointerCast<Constant>(this->expression->rArg)->value;
        
        this->optimizedExpression=createConstant(val1 * val2);
        return true;
    }
    
    if(isTypeOf<Constant>(this->expression->lArg)){
        double val=SPointerCast<Constant>(this->expression->lArg)->value;
        if(val == 0.0){
            this->optimizedExpression=createConstant(0.0);
            return true;
        }
        
        if(val == 1.0){
            this->optimizedExpression=this->expression->rArg;
            return true;
        }
    }
    
    if(isTypeOf<Constant>(this->expression->rArg)){
        double val=SPointerCast<Constant>(this->expression->rArg)->value;
        if(val == 0.0){
            this->optimizedExpression=createConstant(0.0);
            return true;
        }
        
        if(val == 1.0){
            this->optimizedExpression=this->expression->lArg;
            return true;
        }
    }
    
    return false;
}