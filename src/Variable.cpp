/**
 * \file Variable.cpp
 *
 * \brief Implementation of syntax tree node denoting variable in expression.
 *
 * \since 07.05.2016
 * \author agor
 */

#include "Variable.h"
#include "Visitor.h"

Variable::Variable(string name) : Expression(name) {}

 void Variable::accept(Visitor &visitor) const {
	visitor.visit(*this);
}
