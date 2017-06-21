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
	EConstant = 0, ///< Expression is an instance of Constant
	EVariable = 1, ///< Expression is an instance of Variable
	EFunction = 2 ///< Expression is an instance of Function
};


class Expression {
private:
	string name;
	ExpressionType type;
	
protected:
	Expression(string name, ExpressionType type);	
	
public:
	string getName() const;
	ExpressionType getType() const;

	void virtual traverse(Visitor & ) const throw(TraverseException) = 0;
};

#endif /* SRC_EXPRESSION_H_ */
