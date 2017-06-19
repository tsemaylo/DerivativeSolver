/**
 * @file Constant.cpp
 * @brief A constant expression
 * @since 25.03.2016
 * @uthor agor
 */

#include "Constant.h"
#include "Visitor.h"

Constant::Constant(string name) : Expression(name){}

void Constant::accept(Visitor &visitor) const {
	visitor.visit(*this);
}
