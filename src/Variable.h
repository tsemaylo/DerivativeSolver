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
#include "StringGenerator.h"

class Differentiator;

using namespace std;

class Variable: public Expression {
public:
	Variable(string name);
	virtual ~Variable();

	Expression *differentiate(const Differentiator &differentiator) const;
	string printToString(const StringGenerator &sgen) const;
};

#endif /* SRC_VARIABLE_H_ */
