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
    PMult typedExpr=SPointerCast<Mult>(this->expression);
    
    if(isTypeOf<Constant>(typedExpr->lArg) && isTypeOf<Constant>(typedExpr->rArg)){
        double val1=SPointerCast<Constant>(typedExpr->lArg)->value;
        double val2=SPointerCast<Constant>(typedExpr->rArg)->value;
        
        this->optimizedExpression=createConstant(val1 * val2);
        return true;
    }
    
    if(isTypeOf<Constant>(typedExpr->lArg)){
        double val=SPointerCast<Constant>(typedExpr->lArg)->value;
        if(val == 0.0){
            this->optimizedExpression=createConstant(0.0);
            return true;
        }
        
        if(val == 1.0){
            this->optimizedExpression=typedExpr->rArg;
            return true;
        }
    }
    
    if(isTypeOf<Constant>(typedExpr->rArg)){
        double val=SPointerCast<Constant>(typedExpr->rArg)->value;
        if(val == 0.0){
            this->optimizedExpression=createConstant(0.0);
            return true;
        }
        
        if(val == 1.0){
            this->optimizedExpression=typedExpr->lArg;
            return true;
        }
    }
    
    return false;
}