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

/**
 * The Optimizer is intended to simtlify the Expression.
 * 
 * The Optimizer must allways return the new syntax tree!
 * This allows to implement proper iterative simplification of expression:
 * each optimization will generate new tree and therefore it will be possible to
 * compare current optimization with previous result. In other words input expression 
 * should be structurally immutable here. 
 */
class Optimizer : public Visitor {
private:
    /* the optimized expression
     Consideration: the result SPointer must not be the same as  expr
     * argimet of visit() method!
     */
    PExpression result; 
    
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

/**
 * Simplify the given expression.
 * 
 * This function is a facade for Optmizer.
 * 
 * @param expr Expression to be optimized.
 * @return The SPointer to the optimized Expression (it can be in factthe same SPointer as an input.)
 */
PExpression optimize(PExpression expr) throw (TraverseException);

#endif /* OPTIMIZER_H */

