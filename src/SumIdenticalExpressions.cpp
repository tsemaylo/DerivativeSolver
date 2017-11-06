/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumIdenticalExpressions.cpp
 * 
 * Implementation of SumIdenticalExpressions class.
 * 
 * @author agor
 * @since 06.11.2017
 */

#include "SumIdenticalExpressions.h"

#include <ios>
#include <iomanip>
#include <sstream>
#include <Sum.h>
#include <Mult.h>
#include <Constant.h>
#include <Variable.h>
#include <ExpressionFactory.h>
#include "ExceptionThrower.h"

SumIdenticalExpressions::SumIdenticalExpressions(PSum _expression) : OptimizationRule(_expression) {
}

bool SumIdenticalExpressions::apply() throw(TraverseException) {
    PSum typedExpression = SPointerCast<Sum>(this->expression);
    
    // is it appliable?
    // criteria:
    // - both left and right summation arguments contain equal expressions
    // - both left and right summation arguments complemented by constants
    
    if(!isTypeOf<Mult>(typedExpression->lArg) && !isTypeOf<Mult>(typedExpression->rArg)){
        if(equals(typedExpression->lArg, typedExpression->rArg)){
            // summation terms are the same
            this->optimizedExpression=createMult(createConstant("2"), typedExpression->lArg);
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
        sumTerm1=createMult(createConstant("1"),typedExpression->lArg);
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
        sumTerm2=createMult(createConstant("1"),typedExpression->rArg);
    }
    
    // allright, now both sumation terms are represented as Multiplication with 
    // a constant as left arg
    
    if(!equals(sumTerm1->rArg, sumTerm2->rArg)){
        // rule does not appliable because there are no common factor
        return false;
    }
    
    // calculate sum of quotients of common factor
    double val1 = 0.0;
    double val2 = 0.0;
    try {
        val1 = std::stod(SPointerCast<Constant>(sumTerm1->lArg)->value);
        val2 = std::stod(SPointerCast<Constant>(sumTerm2->lArg)->value);

        std::stringstream strStream;
        strStream << std::fixed << std::setprecision(2) << (val1 + val2);
        
        PConstant sumOfConstants = createConstant(strStream.str());
        this->optimizedExpression=createMult(sumOfConstants, sumTerm1->rArg);
        return true;
    }
    catch (std::exception ex) {
        // re-throw an exception
        THROW(TraverseException, ex.what(), "N.A.");
    }
}


