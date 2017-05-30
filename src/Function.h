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

#include "Expression.h"
#include "Differentiator.h"
#include "StringGenerator.h"


class Differentiator;

using namespace std;

class Function: public Expression {
private:
	vector<const Expression *> arguments;

public:
	Function(string name);
	virtual ~Function();

	const Expression *getArgument(const int i);
	void addArgument(const Expression *expression);

	Expression *differentiate(const Differentiator &differentiator) const;
	string printToString(const StringGenerator &sgen) const;
};

#endif /* SRC_FUNCTION_H_ */
