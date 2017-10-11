/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * \file Variable.h
 *
 * \brief Definition of syntax tree node denoting variable in expression.
 *
 * \since 07.05.2016
 * \author agor
 */

#ifndef SRC_VARIABLE_H_
#define SRC_VARIABLE_H_

#include <string>

#include "Expression.h"

using namespace std;

class Variable : public Expression, public EnableSPointerFromThis<Variable> {
private:
    Variable();

public:
    const string name;

    Variable(string name);

    void traverse(Visitor &) const throw (TraverseException) final;

    bool isComplete() const final;
    
    template <class ExpressionClass>
    friend bool isTypeOf(PExpression exprInstance);    
};

// shortcuts for pointers
typedef SPointer<Variable> PVariable;
typedef SPointer<const Variable> PConstVariable;

#endif /* SRC_VARIABLE_H_ */
