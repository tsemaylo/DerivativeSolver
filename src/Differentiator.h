/**
 * @file Differentiator.h
 *
 * @brief Interface for differentiating Visitor for Expression tree.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_DIFFERENTIATOR_H_
#define SRC_DIFFERENTIATOR_H_

#include <Visitor.h>
#include "TraverseException.h"

using namespace std;

class Differentiator : public Visitor {
private:
    PExpression result;
    string variable;
public:
    Differentiator(string var);

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

#endif /* SRC_DIFFERENTIATOR_H_ */
