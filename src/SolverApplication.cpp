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
#include "Parser.h"
#include "Differentiator.h"
#include "StringGenerator.h"

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
	Parser parser;
	Expression *expr = parser.parse(this->strExpression);

	Differentiator differentiator=Differentiator(this->strVariable);
	expr->accept(differentiator);
	
	StringGenerator stringGenerator;
	// @TODO hie must be result expression
	differentiator.getLastVisitResult()->accept(stringGenerator);

	cout << stringGenerator.getLastVisitResult() << endl;
	
	return 0;
}
