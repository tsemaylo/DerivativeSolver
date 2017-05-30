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

#include "Expression.h"
#include "StringGenerator.h"

class Differentiator;

using namespace std;

class Constant: public Expression
{
public:
	Constant(string name);
	virtual ~Constant();

	Expression *differentiate(const Differentiator &differentiator) const;
	string printToString(const StringGenerator &sgen) const;
};

#endif /* SRC_CONSTANT_H_ */
