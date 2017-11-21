/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file OptimizationRule.h
 * 
 * The definition of interface for expression optimization rules.
 * 
 * @author agor
 * @since 11.09.2017
 */
#ifndef OPTIMIZATIONRRULE_H
#define OPTIMIZATIONRRULE_H

#include <Expression.h>
#include <TraverseException.h>

/**
 * Interface for expression optimization rules.
 * 
 * Any expression considers a big variety of optimization cases. The rough estimation 
 * shows that for only one operation like summation there are about 5 basic possibilities 
 * to simplify the  expression. Considering other operations and functions it can be 
 * more than 20 different rules. Under these conditions the implementation of Optimizer 
 * will be bloated with the optimization logic. It will be hard to maintain and eventually 
 * to test the Optimizer visitor. Therefore the logic of optimization rules is encapsulated 
 * within specific implementations of OptimizationRule, where each specialization 
 * (implementation of OptimizationRule interface) is responsible for its own optimization case.
 * 
 * @param ExpressionType Is a pointer type of the Expression subcalss of expression to be optimized.
 */
template <typename ExpressionType>
class OptimizationRule{
protected:
    ExpressionType expression;
    PExpression optimizedExpression;
    
    /**
     * @param _expression Expression to be optimized of the given type ExpressionType.
     */
    OptimizationRule(ExpressionType _expression) : expression(_expression), optimizedExpression(_expression) {
        
    }
    
public:
    /**
     * Apply rule to the Expression. Assuming that the Expression is already known 
     * to the interface implementation, for instance it can be passed via constructor.
     * 
     * @return true if the given expression has been optimized., false otherweise.
     */
    virtual bool apply() throw (TraverseException) = 0;
    
    /**
     * The optimized expression.
     * 
     * If the expression was not optimized the function returns the original one.
     * This function must never return NULL or nullptr.
     * 
     * @return The instance of Expression.
     */
    PExpression getOptimizedExpression() const  {
        return this->optimizedExpression;
    }
};

#endif /* OPTIMIZATIONRRULE_H */