/**
 * \file   main.cpp
 * 
 * \brief main() function initialization of Application.
 * 
 * \version $Revision: $ (SVN)
 * \date $Date: $ (SVN)
 * \author agor
 */

#include <cstdlib>
#include "SolverApplication.h"

using namespace std;

/*
 * 
 */
int main(int argc, char** argv)
{
	SolverApplication app;

	if (argc == 3)
	{
		app.setStrExpression(string(argv[1]));
		app.setStrVariable(string(argv[2]));
	}

	return app.run();
}

