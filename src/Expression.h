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

class Differentiator;
class StringGenerator;

using namespace std;

class Expression {
public:
	Expression(string name);
	virtual ~Expression();

	virtual Expression *differentiate(const Differentiator &differentiator) const =0;
	virtual string printToString(const StringGenerator &sgen) const =0;

	string getName() const;

private:
	string name;
};

#endif /* SRC_EXPRESSION_H_ */
