/**
 * @file Solver.h
 *
 * @brief Client interface to differentiate the expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_SOLVER_H_
#define SRC_SOLVER_H_

#include <string>
#include "Expression.h"

using namespace std;

class Solver {
public:
	Solver();
	virtual ~Solver();

	Expression *solve(const Expression &expr, const string &var) const;
};

#endif /* SRC_SOLVER_H_ */
