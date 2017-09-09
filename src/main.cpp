/**
 * \file   main.cpp
 * 
 * \brief main() function initialization of Application.
 * 
 * \version $Revision: $ (SVN)
 * \date $Date: $ (SVN)
 * \author agor
 */

#include <string>
#include "SolverApplication.h"

/*
 * 
 */
int main(int argc, char** argv) {
    SolverApplication app;

    if (argc == 3) {
        app.setStrExpression(std::string(argv[1]));
        app.setStrVariable(std::string(argv[2]));
    }

    return app.run();
}

