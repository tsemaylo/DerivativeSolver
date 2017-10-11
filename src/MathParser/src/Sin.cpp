/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Sin.cpp
 * 
 * Implemntation of Sin class.
 * 
 * @author  agor
 * @since   16.08.2017
 */

#include "Sin.h"
#include "Visitor.h"
#include "TraverseException.h"

Sin::Sin() : Expression(ESin) {
}

bool Sin::isComplete() const {
    return (this->arg!=nullptr);
}

void Sin::traverse(Visitor& visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}


