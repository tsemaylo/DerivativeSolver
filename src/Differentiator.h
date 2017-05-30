/**
 * @file Differentiator.h
 *
 * @brief Interface for differentiating Visitor for Expression tree.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_DIFFERENTIATOR_H_
#define SRC_DIFFERENTIATOR_H_

#include "Expression.h"
#include "Constant.h"
#include "Variable.h"
#include "Function.h"

using namespace std;

class Function;
class Variable;
class Constant;

class Differentiator {
public:
	Differentiator(string var);
	virtual ~Differentiator();

	/**
	 * @brief Differentiate constant.
	 */
	Expression *solve(const Constant &expr) const;

	/**
	 * @brief Differentiate variable.
	 */
	Expression *solve(const Variable &expr) const;

	/**
	 * @brief Differentiate function.
	 */
	Expression *solve(const Function &expr) const;

private:
	string variable;
};

#endif /* SRC_DIFFERENTIATOR_H_ */
