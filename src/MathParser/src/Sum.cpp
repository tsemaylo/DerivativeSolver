/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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
#include "TraverseException.h"

Sum::Sum() : Expression(ESum) {}

void Sum::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_from_this());
}

bool Sum::isComplete() const{
	return (this->lArg!=nullptr && this->rArg!=nullptr);
}