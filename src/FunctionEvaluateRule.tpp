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
#include <Expression.h>
#include <TraverseException.h>

/**
 * This optimization rule is intended to evaluate expressions representing \n #
 * functions of constants
 */
template <typename T>
class FunctionEvaluateRule : public OptimizationRule<PExpression> {
    private:
        std::function<double(double)> f;
    public:
        FunctionEvaluateRule(PExpression _expression, std::function<double (double)> f);
        bool apply() throw(TraverseException) final;
};

template<typename T>
FunctionEvaluateRule<T>::FunctionEvaluateRule(PExpression _expression, std::function<double (double)> _f) : OptimizationRule(_expression), f(_f) {
}

template<typename T>
bool FunctionEvaluateRule<T>::apply() throw(TraverseException) {
    if(isTypeOf<T>(this->expression)){
        auto typedExpr = SPointerCast<T>(this->expression);
        if(isTypeOf<Constant>(typedExpr->arg)){
            this->optimizedExpression=createConstant(this->f(SPointerCast<Constant>(typedExpr)->value));
            return true;
        }
        return false;
    }
    return false;
}
#endif /* FUNCTIONEVALUATERULE_H */