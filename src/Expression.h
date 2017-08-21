/**
 * @file Expression.h
 *
 * @brief Abstract expression class
 *
 * @since 25.03.2016
 * @author: agor
 */

#ifndef SRC_EXPRESSION_H_
#define SRC_EXPRESSION_H_

#include <string>
#include "TraverseException.h"

class Visitor;

using namespace std;

/** 
 * @brief Type of expression.
 * 
 * well...it is workaround to identify the concrete type of Expression, 
 * but looks like a more clean option instead of dynamic_casts and trying to catch 
 * his exceptions, 
 * or another one visitor and so on,
 * or even in bilt-in std::visit() from c++17.
 * 
 * The type of Expression must be known, for instance, during reduction of a stack
 * of non-terminals by applying of a grammatical rule.
 */
enum ExpressionType {
    EConstant = 0, ///< Expression is an instance of Constant.
    EVariable = 1, ///< Expression is an instance of Variable.
    ESum = 2, ///< Expression is an instance of Summation operator.
    ESub = 3, ///< Expression is an instance of Subtraction operator.
    EDiv = 4, ///< Expression is an instance of Division operator.
    EMult = 5, ///< Expression is an instance of Multiplication operator.
    EPow = 6, ///< Expression is an instance of exponentation operator (rising to the n-th power).
    ESin = 7, ///< Expression for sine functions.
    ECos = 8,  ///< Expression for cosine functions.
    ETan = 9, ///< Expression for tangent functions.
    ECtan = 10,  ///< Expression for cotangent functions.
    ELn = 11,  ///< Expression for natural logarithm functions.
    EExp = 12 ///< Expression for exponential function of basis e.
};

class Expression {
protected:
    Expression(ExpressionType type);

public:
    const ExpressionType type;
    bool virtual isComplete() const = 0;
    bool isFunctionType() const;
    void virtual traverse(Visitor &) const throw (TraverseException) = 0;
};

#endif /* SRC_EXPRESSION_H_ */
