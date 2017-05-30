/**
 * \file Variable.cpp
 *
 * \brief Implementation of syntax tree node denoting variable in expression.
 *
 * \since 07.05.2016
 * \author agor
 */

#include "Variable.h"
#include "Differentiator.h"

Variable::Variable(string name) :
		Expression(name) {
}

Variable::~Variable() {
}

Expression *Variable::differentiate(
		const Differentiator &differentiator) const {
	return differentiator.solve(*this);
}

string Variable::printToString(const StringGenerator &sgen) const {
	return sgen.render(*this);
}

