/**
 * @file StringGenerator.h
 * @brief Interface of the generator of a string representation of an Expression.
 * @since 26.03.2016
 * @author agor
 */

#ifndef SRC_STRINGGENERATOR_H_
#define SRC_STRINGGENERATOR_H_

#include <string>
#include "Visitor.h"

class TraverseException;

using namespace std;

class StringGenerator : public Visitor {
private:
    string result;

    string getArgString(const PConstExpression argExpr) throw (TraverseException);

    template <typename PointerOpClass>
    void visitArythmeticalOp(const PointerOpClass expr, string op) throw (TraverseException);

    template <typename PointerOpClass>
    void visitFunction(const PointerOpClass expr, string fname) throw (TraverseException);

public:
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

    void setLastVisitResult(string result);

    string getLastVisitResult() const;
};

#endif /* SRC_STRINGGENERATOR_H_ */
