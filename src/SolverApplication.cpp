/* 
 * \file   SolverApplication.h
 * 
 * \brief Implementation of Application class.
 * 
 * \version $Revision: $ (SVN)
 * \date $Date: $ (SVN)
 * \author agor
 */

#include <iostream>
#include "SolverApplication.h"
#include "Expression.h"
#include "Solver.h"
#include "Parser.h"
#include "ExpressionPrinter.h"

SolverApplication::SolverApplication() {
}

SolverApplication::~SolverApplication() {
}

void SolverApplication::setStrExpression(const string strExpression)
{
	this->strExpression=strExpression;
}

string SolverApplication::getStrExpression() const
{
	return this->strExpression;
}

void SolverApplication::setStrVariable(const string strVariable)
{
	this->strVariable=strVariable;
}

string SolverApplication::getStrVariable() const
{
	return this->strVariable;
}

int SolverApplication::run()
{
	Parser parser = Parser();
	Expression *expr = parser.parse(this->strExpression);

	Solver solver=Solver();
	Expression *solution=solver.solve(*expr, this->strVariable);

	ExpressionPrinter printer = ExpressionPrinter();
	printer.print(*solution);
	
	return 0;
}
