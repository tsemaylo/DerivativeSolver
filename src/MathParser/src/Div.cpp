/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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
#include "TraverseException.h"

Div::Div() : Expression(EDiv) {}

void Div::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_from_this());
}

bool Div::isComplete() const{
	return (this->lArg!=nullptr && this->rArg!=nullptr);
}