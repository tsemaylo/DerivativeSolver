/**
 * @file   Mult.h
 * 
 * Abstraction for expression for multiplication operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef MULT_H
#define MULT_H

#include "Expression.h"

class Mult : public Expression, public enable_shared_from_this<Mult> {
public:
    PExpression lArg;
    PExpression rArg;

    Mult();

    void traverse(Visitor &) const throw (TraverseException) final;

    bool isComplete() const final;
};

// shortcuts for pointers
typedef SPointer<Mult> PMult;
typedef SPointer<const Mult> PConstMult;

#endif /* MULT_H */

