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
    const std::string value;

    Constant(std::string value);

    void traverse(Visitor &) const throw (TraverseException) final;
    bool isComplete() const final;
    
    template <class ExpressionClass>
    friend bool isTypeOf(SPointer<Expression> exprInstance);    
};

// shortcuts for pointers
typedef SPointer<Constant> PConstant;
typedef SPointer<const Constant> PConstConstant;

#endif /* SRC_CONSTANT_H_ */
