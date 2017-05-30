/**
 * @file Constant.cpp
 * @brief A constant expression
 * @since 25.03.2016
 * @uthor agor
 */

#include "Constant.h"
#include "Differentiator.h"
#include "StringGenerator.h"

Constant::Constant(string name) : Expression(name){
}

Constant::~Constant() {
	// TODO Auto-generated destructor stub
}

Expression *Constant::differentiate(const Differentiator &differentiator) const
{
	return differentiator.solve(*this);
}

string Constant::printToString(const StringGenerator &sgen) const
{
	return sgen.render(*this);
}



