/**
 * @file Function.h
 *
 * @brief Definition of syntax node representing function.
 *
 * @since 27.04.2016
 * @author agor
 */

#ifndef SRC_FUNCTION_H_
#define SRC_FUNCTION_H_

#include <vector>
#include <string>
#include <memory>

#include "Expression.h"

class Differentiator;

using namespace std;

class Function: public Expression {
private:
	vector<unique_ptr<Expression>> arguments;

public:
	Function(string name);

	void addArgument(unique_ptr<Expression> &&expr);
	
	void traverse(Visitor &) const throw(TraverseException) final;
};

#endif /* SRC_FUNCTION_H_ */
