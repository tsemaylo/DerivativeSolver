/**
 * @file Constant.cpp
 * @brief A constant expression
 * @since 25.03.2016
 * @uthor agor
 */

#include "Constant.h"
#include "Visitor.h"

Constant::Constant(string value) : Expression(EConstant), value(value){}

void Constant::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_ptr<const Constant>(this));
}

bool Constant::isComplete() const{
	return true;
}
