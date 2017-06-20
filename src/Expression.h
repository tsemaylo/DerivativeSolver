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

class Expression {
private:
	string name;
	
public:
	Expression(string name);	
	string getName() const;

	void virtual traverse(Visitor & ) const throw(TraverseException) = 0;
};

#endif /* SRC_EXPRESSION_H_ */
