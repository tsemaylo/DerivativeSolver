/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   Sub.cpp
 * 
 * Expression for subtraction operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#include "Sub.h"
#include "Visitor.h"
#include "TraverseException.h"

Sub::Sub() : Expression(ESub) {}

void Sub::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_from_this());
}

bool Sub::isComplete() const{
	return (this->lArg!=nullptr && this->rArg!=nullptr);
}