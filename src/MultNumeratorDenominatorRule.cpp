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

/**
 * The reducable pair is a pair of left and right term of multiplication OP
 * It is reducable when:
 * 1. either e1 or e2 is Div
 * 2. denominator of Div is an exponent or can be seen as exponent of 1 (pow1)
 * 3. other multiplier is an exponent or can be seen as exponent of 1 (pow2)
 * 4. the l-argument of pow1 is equal to l-argument of pow2 
 * 
 * @param e1
 * @param e2
 * 
 * @return 
 */
bool reduceMultipliers(PExpression e1, PExpression e2, std::function<void (PPow, PPow, PExpression)> doReduce) {
    bool e1IsDiv=isTypeOf<Div>(e1);
    bool e2IsDiv=isTypeOf<Div>(e2);
   
    if(!e1IsDiv && !e2IsDiv) {
       return false;
    }
   
    if(e1IsDiv && e2IsDiv) {
       // more complex case, it must be a smarter way to optimize it
       // @TODO consider this case
       return false;
    }
   
   PDiv division;
   PExpression multiplier;
   
    if(e1IsDiv){
       division=e1;
       multiplier=e2;
    }
   
    if(e2IsDiv){
       division=e2;
       multiplier=e1;
    }
   
    PPow pow1;
    PPow pow2;
    if(isTypeOf<Pow>(division->rArg)){
        PPow typed=SPointerCast<Pow>(division->rArg);
        pow1 = createPow(typed->lArg, typed->rArg);
    } else {
        pow1 = createPow(division->rArg, createConstant(1.0));
    }
       
    if(isTypeOf<Pow>(multiplier)){
        PPow typed=SPointerCast<Pow>(multiplier); 
        pow2 = createPow(typed->lArg, typed->rArg);
    } else {
        pow2 = createPow(multiplier, createConstant(1.0));
    }
       
    if(equals(pow1->lArg, pow2->lArg)){
        doReduce(pow1, pow2, division->lArg);
        return true;
    }
    
    return false;
}

PExpression multiplyExponents(PPow e1, PPow e2) {
    
}

bool MultNumeratorDenominatorRule::apply() const throw(TraverseException){
    /**
     * The procedure:
     * 1. represent left and right multiplier as a product 
     * 2. analyze all combinations of arguments of these products to find the pair of arguments which can be reduced
     *    - one argument in this case must be a division operation
     *    - other one is any expression (which seen as exponentiation with some base)
     *    - the denominator of div function can be represented as pow which base is equal to the base of other expression (see above)#
     * 3. reduce the product/division (depends on power exponent) of found pair of arguments
     */
    
    
    // make sure that both larg and rarg of are products 
    PMult lMult;
    if(isTypeOf<Mult>(this->expression->lArg)) {
        lMult=createMult(this->expression->lArg, this->expression->rArg);
    } else {
        lMult=createMult(createConstant(1.0), this->expression);
    }
    
    PMult rMult;
    if(isTypeOf<Mult>(this->expression->lArg)) {
        rMult=createMult(this->expression->lArg, this->expression->rArg);
    } else {
        rMult=createMult(createConstant(1.0), this->expression);
    }
            
    // check different combination of arguments to find reducable pair
    if(reduceMultipliers(lMult->lArg, rMult->lArg, [this](PPow e1, PPow e2, PExpression coef){
        // reduce a pair of expressions
        this->optimizedExpression = createMult(createMult(lMult->rArg, createMult(coef, rMult->rArg)), multiplyExponents(e1, e2));
    })){
        return true;
    }
    
    if(reduceMultipliers(lMult->lArg, rMult->rArg, [this](PPow e1, PPow e2, PExpression coef){
        this->optimizedExpression = createMult(createMult(lMult->rArg, createMult(coef, rMult->lArg)), multiplyExponents(e1, e2));
    })){
        return true;
    }
    
    if(reduceMultipliers(lMult->rArg, rMult->lArg, [this](PPow e1, PPow e2, PExpression coef){
        this->optimizedExpression = createMult(createMult(lMult->lArg, createMult(coef, rMult->rArg)), multiplyExponents(e1, e2));
    })){
        return true;
    }
    
    if(reduceMultipliers(lMult->rArg, rMult->rArg, [this](PPow e1, PPow e2, PExpression coef){
        this->optimizedExpression = createMult(createMult(lMult->lArg, createMult(coef, rMult->lArg)), multiplyExponents(e1, e2));
    })){
        return true;
    }
    
    return false;
}

