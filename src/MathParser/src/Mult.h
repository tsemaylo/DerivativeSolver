/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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

class Mult : public Expression, public EnableSPointerFromThis<Mult> {
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

