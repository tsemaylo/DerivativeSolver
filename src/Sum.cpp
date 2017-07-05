/**
 * @file   Sum.cpp
 * 
 * Expression for summation operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#include "Sum.h"
#include "Visitor.h"

Sum::Sum() : Expression(ESum) {}

void Sum::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(*this);
}
