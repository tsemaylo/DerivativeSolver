/**
 * @file   Sub.h
 * 
 * Abstraction for expression for subtraction operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef SUB_H
#define SUB_H

#include "Expression.h"

class Sub : public Expression, public EnableSPointerFromThis<Sub> {
public:
    PExpression lArg;
    PExpression rArg;

    Sub();

    void traverse(Visitor &) const throw (TraverseException) final;

    bool isComplete() const final;
};

// shortcuts for pointers
typedef SPointer<Sub> PSub;
typedef SPointer<const Sub> PConstSub;

#endif /* SUB_H */

