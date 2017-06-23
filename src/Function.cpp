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

using namespace std;

Function::Function(string name) : Expression(name, EFunction){ }

void Function::addArgument(unique_ptr<Expression> &&expression){
	this->arguments.push_back(move(expression));
}

void Function::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(*this);
}