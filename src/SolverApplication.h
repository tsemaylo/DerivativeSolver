/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   SolverApplication.h
 * 
 * Definition of application class.
 * 
 * @author agor
 */

#ifndef SOLVERAPPLICATION_H
#define SOLVERAPPLICATION_H

#include <string>

using namespace std;

/**
 * Class which intended to implement the solver application logic.
 */
class SolverApplication {
public:
    SolverApplication();
    virtual ~SolverApplication();

    int run();

    void setStrExpression(const string strExpression);

    void setStrVariable(const string strVariable);

private:
    string strExpression;
    string strVariable;
};

#endif /* SOLVERAPPLICATION_H */

