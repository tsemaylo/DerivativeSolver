/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Constant.h
 *
 * @brief Constants.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_CONSTANT_H_
#define SRC_CONSTANT_H_

#include <string>
#include "Expression.h"

class Constant : public Expression, public EnableSPointerFromThis<Constant> {
private:
    Constant();
    
public:
    const double value;

    Constant(double value);

    void traverse(Visitor &) const throw (TraverseException) final;
    bool isComplete() const final;
    
    template <class ExpressionClass>
    friend bool isTypeOf(SPointer<Expression> exprInstance);    
};

// shortcuts for pointers
typedef SPointer<Constant> PConstant;
typedef SPointer<const Constant> PConstConstant;

#endif /* SRC_CONSTANT_H_ */
