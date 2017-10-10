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
#include "Pointers.h"
#include "TraverseException.h"

class Visitor;

/** 
 * @brief Type of expression.
 * 
 * well...it is workaround to identify the concrete type of Expression, 
 * but looks like a more clean option instead of dynamic_casts and trying to catch 
 * his exceptions, 
 * or another one visitor and so on,
 * or even in bilt-in std::visit() from c++17.
 * or typeid which seems to be not so portable.
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
private:
    const ExpressionType type;
    
protected:
    Expression(ExpressionType type);

public:
    bool virtual isComplete() const = 0;
    void virtual traverse(Visitor &) const throw (TraverseException) = 0;
    
    template <class ExpressionClass>
    friend bool isTypeOf(SPointer<Expression> exprInstance);
};

// shortcuts for pointers
typedef SPointer<Expression> PExpression;
typedef SPointer<const Expression> PConstExpression;

/**
 * Check the concrete type of an instance of given Expression .
 * 
 * The template function isTypeOf used to ensure the proper type of the Expeession.
 * Unfortunately its implementation looks also not so clean. 
 * The further refactoring is cosidered (especially regardingb the usage of private constructors and friend functions).
 * 
 * @param ExpressionClass The assumed type of the Expression.
 * @param exprInstance The instance of Expression.
 * 
 * @return true if exprInstance is ExpressionClass type, otherweis - false. 
 */
template <class ExpressionClass>
bool isTypeOf(PExpression exprInstance){
    ExpressionClass dummy;
    return (exprInstance->type == dummy.type);
}

/**
 * Get a string representation of an expression.
 *  
 * @param expr The expression.
 * @return Readable string representing the expr.
 */
std::string to_string(const PExpression expr);

/**
 * Check whether the two given expressions are identical.
 * 
 * @param exprL First expression (left-hand).
 * @param exprR Second expression (right-hand).
 * 
 * @return true if expressions are equal, otherwise - false.
 */
bool equals(const PExpression exprL, const PExpression exprR) throw (TraverseException);

#endif /* SRC_EXPRESSION_H_ */
