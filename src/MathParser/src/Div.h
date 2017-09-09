/**
 * @file   Div.h
 * 
 * Abstraction for expression for division operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef DIV_H
#define DIV_H

#include "Expression.h"

class Div : public Expression, public EnableSPointerFromThis<Div> {
public:
    PExpression lArg;
    PExpression rArg;

    Div();

    void traverse(Visitor &) const throw (TraverseException) final;

    bool isComplete() const final;
};

// shortcuts for pointers
typedef SPointer<Div> PDiv;
typedef SPointer<const Div> PConstDiv;

#endif /* DIV_H */

