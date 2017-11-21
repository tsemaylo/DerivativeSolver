/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     FunctionEvaluateRule.tpp
 * 
 * Definition of the FunctionEvaluateRule template class.
 * 
 * @author   agor
 * @since 20.11.2017
 */

#ifndef FUNCTIONEVALUATERULE_H
#define FUNCTIONEVALUATERULE_H

#include "OptimizationRule.tpp"
#include <ExpressionFactory.h>
#include <TraverseException.h>

/**
 * This optimization rule is intended to evaluate expressions representing 
 * functions of constants
 * 
 * @param T Type of the function expression (Sin, Cos etc).
 */
template <typename T>
class FunctionEvaluateRule : public OptimizationRule<PExpression> {
private:
    std::function<double(double) > f;
    
public:

    /**
     * Construct the function evaluator.
     * 
     * @param _expression The Expression of function to be evaluated
     * @param _f Function that performs actual nummeric calculations.
     */
    FunctionEvaluateRule(PExpression _expression, std::function<double (double) > _f) : OptimizationRule(_expression), f(_f) {
    }

    bool apply() throw (TraverseException) final {
        if (isTypeOf<T>(this->expression)) {
            auto typedExpr = SPointerCast<T>(this->expression);
            if (isTypeOf<Constant>(typedExpr->arg)) {
                this->optimizedExpression = createConstant(this->f(SPointerCast<Constant>(typedExpr->arg)->value));
                return true;
            }
            return false;
        }
        return false;
    }
};
#endif /* FUNCTIONEVALUATERULE_H */