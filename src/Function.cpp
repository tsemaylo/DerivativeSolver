/**
 * @file Function.cpp
 *
 * @brief Implementation of syntax node representing function.
 *
 * @since 27.04.2016
 * @author agor
 */

#include "Function.h"

Function::Function(string name) : Expression(name){ }

Function::~Function() {
	// Should I delete the content of arguments list?
	// ... preliminary answer is YES
	//@TODO
}

const Expression *Function::getArgument(const int i) {
	return this->arguments[i];
}

void Function::addArgument(const Expression *expression){
	this->arguments.push_back(expression);
}

Expression *Function::differentiate(const Differentiator &differentiator) const {
	return differentiator.solve(*this);
}

string Function::printToString(const StringGenerator &sgen) const {
	return sgen.render(*this);
}
