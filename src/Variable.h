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

class Variable: public Expression {
public:
	const string name;
	
	Variable(string name);
	
	void traverse(Visitor & ) const throw(TraverseException) final;
	
	bool isComplete() const final;
};

#endif /* SRC_VARIABLE_H_ */
