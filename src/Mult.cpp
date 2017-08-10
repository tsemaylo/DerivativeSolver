/**
 * @file   Mult.cpp
 * 
 * Expression for multiplication operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#include "Mult.h"
#include "Visitor.h"

Mult::Mult() : Expression(EMult) {}

void Mult::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_from_this());
}

bool Mult::isComplete() const{
	return (this->lArg!=nullptr && this->rArg!=nullptr);
}