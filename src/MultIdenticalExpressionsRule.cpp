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
#include "MathParser/src/ExpressionFactory.h"

MultIdenticalExpressionsRule::MultIdenticalExpressionsRule(PMult _expression): OptimizationRule(_expression) {
}

bool castRightArgToPow(PExpression expr, std::function<bool (PPow)> onSuccess){
    if(!isTypeOf<Pow>(expr)){
        onSuccess(createPow(expr, createConstant(1.0)));
        return true;
    }
    
    onSuccess(SPointerCast<Pow>(expr));
    return true;
}

bool putConstantToLeft(PExpression expr, std::function<bool (PMult)> onSuccess){
    if(!isTypeOf<Mult>(expr)){
        onSuccess(createMult(createConstant(1.0), SPointerCast<Mult>(expr)->lArg));
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
        return onSuccess(createMult(typedExpr->rArg, typedExpr->rArg));
    }else{
        return onSuccess(typedExpr);
    }

    return true;
}

bool MultIdenticalExpressionsRule::apply() throw(TraverseException){
    PMult typedExpr=SPointerCast<Mult>(this->expression);
    
    // check if left and right hand terms are also products (Mult)
    bool lArgIsMult=isTypeOf<Mult>(typedExpr->lArg);
    bool rArgIsMult=isTypeOf<Mult>(typedExpr->rArg);
    
    if(!lArgIsMult && !rArgIsMult){ 
        if(equals(typedExpr->lArg, typedExpr->rArg)){
            // x*x = x^2
            this->optimizedExpression=createPow(typedExpr->lArg, createConstant(2.0));
            return true;
        }
        return false;
    }
    
    // try to normalize it to canonical form: A*(x^n) * B*(x^m)
    PMult canonicalForm=createMult(); 
   
    if(!putConstantToLeft(typedExpr->lArg, [&canonicalForm](PMult normalizedLArg) -> bool{
        // now check that the right operand is actually the exponent or can be casted to exponent
        if(!castRightArgToPow(normalizedLArg->rArg, [&normalizedLArg](PPow castedExpression){
            normalizedLArg->rArg=castedExpression;
        })){
            return false; 
        }
        canonicalForm->lArg=normalizedLArg;
        return true;
    })){
        return false;
    }
    
    if(!putConstantToLeft(typedExpr->rArg, [&canonicalForm](PMult normalizedRArg) -> bool{
        if(!castRightArgToPow(normalizedRArg->rArg, [&normalizedRArg](PPow castedExpression){
            normalizedRArg->rArg=castedExpression;
        })){
            return false; 
        }
        canonicalForm->rArg=normalizedRArg;
        return true;
    })){
        return false;
    }
    
    // now check whether arguments of exponentation functions are identical
    PMult canLeftMultTerm = SPointerCast<Mult>(canonicalForm->lArg);
    PPow canLeftPow = SPointerCast<Pow>(canLeftMultTerm->lArg);
    PMult canRightMultTerm = SPointerCast<Mult>(canonicalForm->rArg);
    PPow canRightPow = SPointerCast<Pow>(canRightMultTerm->lArg);
    if(!equals(canLeftPow->lArg, canRightPow->lArg)){
        return false;
    }
    
    // ok, it is time to reorganize the expression
    PConstant ab=createConstant(SPointerCast<Constant>(canLeftMultTerm->lArg)->value * SPointerCast<Constant>(canRightMultTerm->lArg)->value);
    PMult res=createMult(ab, createPow(canLeftPow->lArg, createSum(canLeftPow->rArg, canRightPow->rArg)));
    
    this->optimizedExpression=res;
    return true;
}

