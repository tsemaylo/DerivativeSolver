/**
 * @file OptimizationRule.h
 * 
 * The implementation of interface for expression optimization rules.
 * 
 * @author agor
 * @since 11.09.2017
 */

#include "OptimizationRule.h"
#include "MathParser/src/Expression.h"

OptimizationRule::OptimizationRule(PExpression _expression) : expression(_expression), optimizedExpression(_expression) {
}

PExpression OptimizationRule::getOptimizedExpression() const{
    return this->optimizedExpression;
}