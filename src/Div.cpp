/**
 * @file   Div.cpp
 * 
 * Expression for division operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#include "Div.h"
#include "Visitor.h"

Div::Div() : Expression(EDiv) {}

void Div::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(*this);
}