/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultNumeratorDenominatorRule.cpp
 * 
 * Implementation of the  MultNumeratorDenominatorRule class.
 * 
 * @TODO to be seriously refactored...
 * 
 * @author   agor
 * @since 15.12.2017
 */

#include "MultNumeratorDenominatorRule.h"
#include <ExpressionFactory.h>

MultNumeratorDenominatorRule::MultNumeratorDenominatorRule(PMult _expression) : OptimizationRule(_expression){
}

bool reduciblePair(PExpression denom, PExpression numer, std::function<void (PPow, PPow)> doReduce) {
    // 3.1. reducible means that both examined expressions are in fact exponentiations with the same base
    
    PPow denomExp;
    PPow numExp;
    if(isTypeOf<Pow>(denom)){
        PPow typed=SPointerCast<Pow>(denom);
        denomExp = createPow(typed->lArg, typed->rArg);
    } else {
        denomExp = createPow(denom, createConstant(1.0));
    }
       
    if(isTypeOf<Pow>(numer)){
        PPow typed=SPointerCast<Pow>(numer); 
        numExp = createPow(typed->lArg, typed->rArg);
    } else {
        numExp = createPow(numer, createConstant(1.0));
    }
     
    if(equals(denomExp->lArg, numExp->lArg)){
        doReduce(denomExp, numExp);
        return true;
    }
    
    return false;
}

PExpression reduce(PPow denomExp, PExpression coefB, PPow numExp, PExpression coefA) {
    //4. Having a pair of exponentiation operations (Pows) which can be simplified
    // reduce them them buy adding or subtracting their power exponents

    // 4.1. extract power exponents
    PExpression denomPowExponent = denomExp->rArg;
    PExpression numPowExponent = numExp->rArg;
    if (isTypeOf<Constant>(denomPowExponent) && isTypeOf<Constant>(numPowExponent)) {
        // ok we have constants and we can operate with them

        PConstant castedDenomPowExponent = SPointerCast<Constant>(denomPowExponent);
        PConstant castedNumPowExponent = SPointerCast<Constant>(numPowExponent);

        // 5. Form the result expression by multiplying the coefficients 
        // (larg of left Division and remaining argument of right Multiplication) 
        // and dividing/multiplying them with previously obtained exponentiation  
        if (castedDenomPowExponent->value > castedNumPowExponent->value) {
            // b/x^m * ax^n => (a*b)/x^(m-n), if m > n
            return createDiv(createMult(coefA, coefB),
                    createPow(denomExp->lArg, createConstant(castedDenomPowExponent->value - castedNumPowExponent->value)));
        }
        // b/x^m * ax^n => (a*b)*x^(n-m), if n > m
        return createMult(createMult(coefA, coefB),
                createPow(denomExp->lArg, createConstant(castedNumPowExponent->value - castedDenomPowExponent->value)));
    }
    // if they are not constants do default subtraction of exponents
    // b/x^m * ax^n => (a*b)*x^(n-m)
    return createMult(createMult(coefA, coefB),
            createPow(denomExp->lArg, createSub(numPowExponent, denomPowExponent)));
    
}

bool MultNumeratorDenominatorRule::apply() throw(TraverseException) {
    // Identifying ax^n*b/x^m pattern:
    
    // 1. One of terms must be Division
    bool largIsDiv=isTypeOf<Div>(this->expression->lArg);
    bool rargIsDiv=isTypeOf<Div>(this->expression->rArg);
    
    if(!largIsDiv && !rargIsDiv) { 
       return false;
    }
    if(largIsDiv && rargIsDiv) {
       return false;
    }

    PMult normalizedExpr;
    if(rargIsDiv) {
        // 1.1. if so - put it on the left side of original Multiplication
        normalizedExpr=createMult(this->expression->rArg, this->expression->lArg);
    } else {
        normalizedExpr=createMult(this->expression->lArg, this->expression->rArg);
    }
    
    // 2. Represent right arg of multiplication as Multiplication
    PMult rarg;
    if(isTypeOf<Mult>(normalizedExpr->rArg)){
        PMult casted=SPointerCast<Mult>(normalizedExpr->rArg);
        rarg=createMult(casted->lArg, casted->rArg);
    } else {
        rarg=createMult(createConstant(1.0), normalizedExpr->rArg);
    }
    
    PDiv larg=SPointerCast<Div>(normalizedExpr->lArg);

    // 3. Check whether denominator of left arg Division is reducible with one of arguments of the right arg multiplication
    if(reduciblePair(larg->rArg, rarg->lArg, [this, &larg, &rarg](PPow denomExp, PPow numExp) {
        this->optimizedExpression = reduce(denomExp, larg->lArg, numExp, rarg->rArg);
    })){
        return true;
    }
    
    if(reduciblePair(larg->rArg, rarg->rArg, [this, &larg, &rarg](PPow denomExp, PPow numExp) {
        this->optimizedExpression = reduce(denomExp, larg->lArg, numExp, rarg->lArg);
    })){
        return true;
    }
    
    return false;
}

