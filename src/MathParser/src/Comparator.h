/**
 * @file Comparator.h
 * 
 * Definition of Comparator class. 
 * 
 * @author agor
 * @since 09.10.2017
 */

#ifndef COMPARATOR_H
#define COMPARATOR_H

#include "Visitor.h"

/**
 * The Comparator class is used to traverse the syntax tree and compare it with 
 * the other one. Comparison considers only equalty of expressions. For instance:
 * sin(x) == sin(x), but sin(x) != sin(z).
 */
class Comparator : public Visitor{
private:
    PExpression exprBeingCompared;
    bool result; // true if expressions are equal
    
    /**
     * Wrapper function to perform taype aware checks, like type casts for 
     * generic expression types, null checks and so on.
     * 
     * @param expr Basic Expression to compare.
     * @param f Custom lambda function to perform type related handling of expr. \n
     *          Has two arguments: expr - see above, typedExprBeingComp - the typed expression being compared with expr.
     */
    template<typename T, typename PT>
    void typeAware(PT expr, std::function<bool (PT expr, PT)> f) throw (TraverseException);
    
    /**
     * Generalization of comparison for Expression's of function types (sin, cos, ln etc)
     */
    template<typename T, typename PT>
    void visitFunction(PT expr) throw (TraverseException);
public:
    /**
     * @param expr Expression to compare with
     */
    Comparator(PExpression exprBeingCompared);
    
    void visit(const PConstConstant expr) throw (TraverseException) final;

    void visit(const PConstVariable expr) throw (TraverseException) final;

    void visit(const PConstSum expr) throw (TraverseException) final;
    void visit(const PConstSub expr) throw (TraverseException) final;
    void visit(const PConstDiv expr) throw (TraverseException) final;
    void visit(const PConstMult expr) throw (TraverseException) final;
    void visit(const PConstPow expr) throw (TraverseException) final;
    void visit(const PConstSin expr) throw (TraverseException) final;
    void visit(const PConstCos expr) throw (TraverseException) final;
    void visit(const PConstTan expr) throw (TraverseException) final;
    void visit(const PConstCtan expr) throw (TraverseException) final;
    void visit(const PConstLn expr) throw (TraverseException) final;
    void visit(const PConstExp expr) throw (TraverseException) final;
    
    bool areEqual();
};

#endif /* COMPARATOR_H */

