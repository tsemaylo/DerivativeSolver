/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Cos.cpp
 * 
 * Implemntation of Cos class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#include "Cos.h"
#include "Visitor.h"

Cos::Cos() : Expression(ECos) {
}

bool Cos::isComplete() const {
    return (this->arg!=nullptr);
}

void Cos::traverse(Visitor& visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}
