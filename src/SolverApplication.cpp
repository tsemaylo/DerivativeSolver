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
#include <memory>
#include "SolverApplication.h"
#include "Expression.h"
#include "Parser.h"
#include "Differentiator.h"
#include "StringGenerator.h"

using namespace std;

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
	try{
		unique_ptr<Expression> expr = parser.parse(this->strExpression);

		Differentiator differentiator=Differentiator(this->strVariable);
		expr->traverse(differentiator);

		StringGenerator stringGenerator;
		// @TODO hie must be result expression
		differentiator.getLastVisitResult()->traverse(stringGenerator);

		cout << stringGenerator.getLastVisitResult() << endl;
	}
	
	catch(ParsingException ex){
		cout << "ERROR: " << ex.what();
	}
	
	catch(TraverseException ex){
		cout << "ERROR: " << ex.what();
	}
	
	return 0;
}
