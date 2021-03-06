/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   Sum.h
 * 
 * Abstraction for expression for summation operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef SUM_H
#define SUM_H

#include "Expression.h"

class Sum : public Expression, public EnableSPointerFromThis<Sum> {
public:
    PExpression lArg;
    PExpression rArg;

    Sum();

    void traverse(Visitor &) const throw (TraverseException) final;

    bool isComplete() const final;
};

// shortcuts for pointers
typedef SPointer<Sum> PSum;
typedef SPointer<const Sum> PConstSum;

#endif /* SUM_H */

