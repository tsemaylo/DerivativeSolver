/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     FunctionEvaluateRule.CPPh
 * 
 * Definition of the FunctionEvaluateRule class.
 * 
 * @author   agor
 * @since 20.11.2017
 */

#include "FunctionEvaluateRule.h"

FunctionEvaluateRule::FunctionEvaluateRule(PExpression _expression) : OptimizationRule(_expression){

}

bool FunctionEvaluateRule::apply() throw(TraverseException){
    // how to find out what king on expression is it?
    // see no clean sollutions so far.. 
    
    return false;
}

