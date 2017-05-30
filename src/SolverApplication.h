/* 
 * \file   SolverApplication.cpp
 * 
 * \brief Class which intended to implement the application logic.
 * 
 * \version $Revision: $ (SVN)
 * \date $Date: $ (SVN)
 * \author agor
 */

#ifndef SOLVERAPPLICATION_H
#define SOLVERAPPLICATION_H

#include <string>

using namespace std;

class SolverApplication
{
public:
	SolverApplication ();
	virtual ~ SolverApplication ();
	
	int run();
	
	void setStrExpression(const string strExpression);
	string getStrExpression() const;
	
	void setStrVariable(const string strVariable);
	string getStrVariable() const;
	
private:
	string strExpression;
	string strVariable;
};

#endif /* SOLVERAPPLICATION_H */

