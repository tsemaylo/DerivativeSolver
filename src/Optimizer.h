/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Optimizer.h
 * 
 * Definition of Optimizer.
 * 
 * @author agor
 * @since 09.09.2017
 */

#ifndef OPTIMIZER_H
#define OPTIMIZER_H

#include <vector>
#include <Visitor.h>

#include "OptimizationRule.h"

class Optimizer : public Visitor {
private:
    PExpression result;
    
    /**
     * Initialize the vector of optimization rules for summation expression.
     * 
     * @param expr The Summation expression.
     * @return Vector consisting of unique pointers to OptimizationRule's.
     */
    inline std::vector<std::unique_ptr<OptimizationRule>> summationRules(PSum expr) const;
    
    /**
     * Initialize the vector of optimization rules for multiplication expression.
     * 
     * @param expr The Mult expression.
     * @return Vector consisting of unique pointers to OptimizationRule's.
     */
    inline std::vector<std::unique_ptr<OptimizationRule>> multiplicationRules(PMult expr) const;
    
    /**
     * Get the negative counterpart of given expression.
     * 
     * For instance: for negateExpression(a) = -a
     * If the expr is Variable or any function the Mult with 
     * "-1" as left argument will be returned.
     * 
     * @param expr The expression to be negated.
     * 
     * @return Negative expression.
     */
    inline PExpression negateExpression(PExpression expr) const throw(TraverseException);
public:
    void visit(const PConstConstant expr) throw (TraverseException) final;
    void visit(const PConstVariable expr) throw (TraverseException) final;
    void visit(const PConstSum expr) throw (TraverseException) final;
    void visit(const PConstSub expr) throw (TraverseException) final;
    void visit(const PConstMult expr) throw (TraverseException) final;
    void visit(const PConstDiv expr) throw (TraverseException) final;
    void visit(const PConstPow expr) throw (TraverseException) final;
    void visit(const PConstSin expr) throw (TraverseException) final;
    void visit(const PConstCos expr) throw (TraverseException) final;
    void visit(const PConstTan expr) throw (TraverseException) final;
    void visit(const PConstCtan expr) throw (TraverseException) final;
    void visit(const PConstLn expr) throw (TraverseException) final;
    void visit(const PConstExp expr) throw (TraverseException) final;

    void setLastVisitResult(const PExpression result);
    PExpression getLastVisitResult() const;
};

#endif /* OPTIMIZER_H */

