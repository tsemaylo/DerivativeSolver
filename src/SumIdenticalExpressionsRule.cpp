/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumIdenticalExpressionsRule.cpp
 * 
 * Implementation of SumIdenticalExpressionsRule class.
 * 
 * @author agor
 * @since 06.11.2017
 */

#include "SumIdenticalExpressionsRule.h"

#include <ios>
#include <iomanip>
#include <sstream>
#include <Sum.h>
#include <Mult.h>
#include <Constant.h>
#include <Variable.h>
#include <ExpressionFactory.h>
#include "ExceptionThrower.h"

SumIdenticalExpressionsRule::SumIdenticalExpressionsRule(PSum _expression) : OptimizationRule(_expression) {
}

bool SumIdenticalExpressionsRule::apply() throw(TraverseException) {
    PSum typedExpression = SPointerCast<Sum>(this->expression);
    
    // is it appliable?
    // criteria:
    // - both left and right summation arguments contain equal expressions
    // - both left and right summation arguments complemented by constants
    
    if(!isTypeOf<Mult>(typedExpression->lArg) && !isTypeOf<Mult>(typedExpression->rArg)){
        if(equals(typedExpression->lArg, typedExpression->rArg)){
            // summation terms are the same
            this->optimizedExpression=createMult(createConstant(2.0), typedExpression->lArg);
            return true;
        }
        // summation terms are completely different - nothing to do
        return false;
    }
    
    // at least one term is multiplication - try to express both terms as Mult
    
    PMult sumTerm1;
    if(isTypeOf<Mult>(typedExpression->lArg)){
        PMult temp=SPointerCast<Mult>(typedExpression->lArg);
        if(!isTypeOf<Constant>(temp->lArg) && !isTypeOf<Constant>(temp->rArg)){
            // one multiplication does not contain constant - nothing to do
            return false;
        }else if(isTypeOf<Constant>(temp->rArg)){
            // right argument is constant - swap arguments
            sumTerm1=createMult(temp->rArg,temp->lArg);
        }else{
            sumTerm1=temp;
        }
    }else{
        sumTerm1=createMult(createConstant(1.0),typedExpression->lArg);
    }
    
    PMult sumTerm2;
    if(isTypeOf<Mult>(typedExpression->rArg)){
        PMult temp=SPointerCast<Mult>(typedExpression->rArg);
        if(!isTypeOf<Constant>(temp->lArg) && !isTypeOf<Constant>(temp->rArg)){
            return false;
        }else if(isTypeOf<Constant>(temp->rArg)){
            sumTerm2=createMult(temp->rArg,temp->lArg);
        }else{
            sumTerm2=temp;
        }
    }else{
        sumTerm2=createMult(createConstant(1.0),typedExpression->rArg);
    }
    
    // allright, now both sumation terms are represented as Multiplication with 
    // a constant as left arg
    
    if(!equals(sumTerm1->rArg, sumTerm2->rArg)){
        // rule does not appliable because there are no common factor
        return false;
    }
    
    // calculate sum of quotients of common factor
    double val1 = SPointerCast<Constant>(sumTerm1->lArg)->value;
    double val2 = SPointerCast<Constant>(sumTerm2->lArg)->value;
    this->optimizedExpression=createMult(createConstant(val1 + val2), sumTerm1->rArg);
    return true;
}


