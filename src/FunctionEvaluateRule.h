/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     FunctionEvaluateRule.h
 * 
 * Definition of the FunctionEvaluateRule class.
 * 
 * @author   agor
 * @since 20.11.2017
 */

#ifndef FUNCTIONEVALUATERULE_H
#define FUNCTIONEVALUATERULE_H

#include "OptimizationRule.h"
#include <TraverseException.h>

/**
 * This optimization rule is intended to evaluate expressions representing \n #
 * functions of constants
 * 
 * @TODO this must be refactored together with OptomizationRule to minimize 
 * dependency from concrete Expresson instances.
 * 
 * @param _expression
 */
class FunctionEvaluateRule : public OptimizationRule{
public:
    FunctionEvaluateRule(PExpression _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* FUNCTIONEVALUATERULE_H */

