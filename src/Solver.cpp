/**
 * @file Solver.cpp
 *
 * @brief Client to use in application which differentiates the expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Solver.h"
#include "Differentiator.h"

Solver::Solver() {
	// TODO Auto-generated constructor stub

}

Solver::~Solver() {
	// TODO Auto-generated destructor stub
}

Expression *Solver::solve(const Expression &expr, const string &var) const
{
	Differentiator differentiator=Differentiator(var);
	return expr.differentiate(differentiator);
}
