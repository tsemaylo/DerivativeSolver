/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/* 
 * \file   SolverApplication.cpp
 * 
 * \brief Implementation of Application class.
 * 
 * \version $Revision: $ (SVN)
 * \date $Date: $ (SVN)
 * \author agor
 */

#include "SolverApplication.h"

#include <iostream>
#include <Expression.h>
#include <Parser.h>
#include <Parser.h>

#include "Differentiator.h"
#include "Optimizer.h"

using namespace std;

SolverApplication::SolverApplication() {
}

SolverApplication::~SolverApplication() {
}

void SolverApplication::setStrExpression(const string strExpression) {
    this->strExpression = strExpression;
}

void SolverApplication::setStrVariable(const string strVariable) {
    this->strVariable = strVariable;
}

int SolverApplication::run() {
    int returnCode=0;
    try {
        PExpression optimized=optimize(differentiate(optimize(parse(this->strExpression)), this->strVariable));

        cout << to_string(optimized) << endl;
    } catch (ParsingException ex) {
        cout << "ERROR: " << ex.what();
        returnCode=1;
    } catch (TraverseException ex) {
        cout << "ERROR: " << ex.what();
        returnCode=1;
    }
    
    return returnCode;
}
