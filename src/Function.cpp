/**
 * @file Function.cpp
 *
 * @brief Implementation of syntax node representing function.
 *
 * @since 27.04.2016
 * @author agor
 */

#include "Function.h"
#include "Visitor.h"

Function::Function(string name) : Expression(name){ }

const Expression *Function::getArgument(const int i) {
	return this->arguments[i];
}

void Function::addArgument(const Expression *expression){
	this->arguments.push_back(expression);
}

void Function::accept(Visitor &visitor) const {
	visitor.visit(*this);
}