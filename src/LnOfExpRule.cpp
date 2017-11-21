/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     LnOfExpRule.cpp
 * 
 * Implementation of the LnOfExpRule class.
 * 
 * @author   agor
 * @since 21.11.2017
 */

#include "LnOfExpRule.h"

#include <ExpressionFactory.h>

LnOfExpRule::LnOfExpRule(PLn _expression) : OptimizationRule(_expression) {
}

bool LnOfExpRule::apply() throw (TraverseException){
    if(isTypeOf<Exp>(this->expression->arg)){
        this->optimizedExpression=SPointerCast<Exp>(this->expression->arg)->arg;
        return true;
    }
    return false;
}

