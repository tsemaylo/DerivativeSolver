/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultNumeratorDenomnator.cpp
 * 
 * Implementation of the  MultNumeratorDenomnator class.
 * 
 * @TODO to be seriously refactored...
 * 
 * @author   agor
 * @since 15.12.2017
 */

#include "MultNumeratorDenomnator.h"
#include <ExpressionFactory.h>

MultNumeratorDenomnator::MultNumeratorDenomnator(PMult _expression) : OptimizationRule(_expression){
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
bool reducablePair(PExpression e1, PExpression e2) {
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
       
    return equals(pow1->lArg, pow2->lArg);
}

PExpression reduce(PPow e1, PDiv e2) {
    
    
}

bool MultNumeratorDenomnator::apply() const throw(TraverseException){
    // make sure that both larg and rarg of are products 
    PMult lMult;
    if(isTypeOf<Mult>(this->expression->lArg)){
        lMult=createMult(this->expression->lArg, this->expression->rArg);
    } else {
        lMult=createMult(createConstant(1.0), this->expression);
    }
    
    PMult rMult;
    if(isTypeOf<Mult>(this->expression->lArg)){
        rMult=createMult(this->expression->lArg, this->expression->rArg);
    } else {
        rMult=createMult(createConstant(1.0), this->expression);
    }
    
    // check different combination of arguments to find reducable pair
    if(reducablePair(lMult->lArg, rMult->lArg, [this](PPow e1, PPow e2){
        // reduce a pair of expressions
        this->optimizedExpression = createMult(createMult(lMult->rArg, rMult->rArg), reduce(e1, e2));
    })){
        return true;
    }
    
    if(reducablePair(lMult->lArg, rMult->rArg)){
        // reduce a pair of expressions
        this->optimizedExpression = createMult(createMult(lMult->rArg, rMult->lArg), reduce(lMult->lArg, rMult->rArg));
        return true;
    }
    if(reducablePair(lMult->rArg, rMult->lArg)){
        // reduce a pair of expressions
        this->optimizedExpression = createMult(createMult(lMult->lArg, rMult->rArg), reduce(lMult->rArg, rMult->lArg));
        return true;
    }
    if(reducablePair(lMult->rArg, rMult->rArg)){
        // reduce a pair of expressions
        this->optimizedExpression = createMult(createMult(lMult->lArg, rMult->lArg), reduce(lMult->rArg, rMult->rArg));
        return true;
    }
    
    return false;
    
}

