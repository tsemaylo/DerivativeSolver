/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultIdenticalExpressionsRule.cpp
 * 
 * Implementation of the  MultIdenticalExpressionsRule class.
 * 
 * @author   agor
 * @since 14.11.2017
 */

#include "MultIdenticalExpressionsRule.h"
#include <ExpressionFactory.h>

MultIdenticalExpressionsRule::MultIdenticalExpressionsRule(PMult _expression): OptimizationRule(_expression) {
}

PPow castRightArgToPow(PExpression expr){
    if(isTypeOf<Pow>(expr)){
        return SPointerCast<Pow>(expr);
    }
    return createPow(expr, createConstant(1.0)); 
}

bool putConstantToLeft(PExpression expr, std::function<bool (PMult)> onSuccess){
    if(!isTypeOf<Mult>(expr)){
        onSuccess(createMult(createConstant(1.0), expr));
        return true;
    }
    
    PMult typedExpr=SPointerCast<Mult>(expr);
    bool lIsConst=isTypeOf<Constant>(typedExpr->lArg);
    bool rIsConst=isTypeOf<Constant>(typedExpr->rArg);
    if(!lIsConst && !rIsConst){
        // product does not contain constant
        // For example: x*y * 3x - I see not too much sense in this optimization
        return false;
    }
        
    if(rIsConst){
        return onSuccess(createMult(typedExpr->rArg, typedExpr->lArg));
    }else{
        // create a new instance of mult to avoid sideeffects
        return onSuccess(createMult(typedExpr->lArg, typedExpr->rArg));
    }

    return true;
}

bool MultIdenticalExpressionsRule::apply() throw(TraverseException){
    // check if left and right hand terms are also products (Mult)
    bool lArgIsMult=isTypeOf<Mult>(this->expression->lArg);
    bool rArgIsMult=isTypeOf<Mult>(this->expression->rArg);
    
    if(!lArgIsMult && !rArgIsMult){ 
        if(equals(this->expression->lArg, this->expression->rArg)){
            // x*x = x^2
            this->optimizedExpression=createPow(this->expression->lArg, createConstant(2.0));
            return true;
        }
    }
    
    // try to normalize it to canonical form: A*(x^n) * B*(x^m)
    PMult canonicalForm=createMult(); 
   
    if(!putConstantToLeft(this->expression->lArg, [&canonicalForm](PMult normalizedLArg) -> bool{
        // now check that the right operand is actually the exponent or can be casted to exponent
        normalizedLArg->rArg=castRightArgToPow(normalizedLArg->rArg);
        canonicalForm->lArg=normalizedLArg;
        return true;
    })){
        return false;
    }
    
    if(!putConstantToLeft(this->expression->rArg, [&canonicalForm](PMult normalizedRArg) -> bool{
        normalizedRArg->rArg=castRightArgToPow(normalizedRArg->rArg);
        canonicalForm->rArg=normalizedRArg;
        return true;
    })){
        return false;
    }
    
    // now check whether arguments of exponentation functions are identical
    PMult canLeftMultTerm = SPointerCast<Mult>(canonicalForm->lArg);
    PPow canLeftPow = SPointerCast<Pow>(canLeftMultTerm->rArg);
    PMult canRightMultTerm = SPointerCast<Mult>(canonicalForm->rArg);
    PPow canRightPow = SPointerCast<Pow>(canRightMultTerm->rArg);
    if(!equals(canLeftPow->lArg, canRightPow->lArg)){
        return false;
    }
    
    // ok, it is time to reorganize the expression
    PConstant ab=createConstant(SPointerCast<Constant>(canLeftMultTerm->lArg)->value * SPointerCast<Constant>(canRightMultTerm->lArg)->value);
    PMult res=createMult(ab, createPow(canLeftPow->lArg, createSum(canLeftPow->rArg, canRightPow->rArg)));
    
    this->optimizedExpression=res;
    return true;
}

