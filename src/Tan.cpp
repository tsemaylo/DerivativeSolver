/**
 * @file    Tan.cpp
 * 
 * Implemntation of Tan class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#include "Tan.h"
#include "Visitor.h"

Tan::Tan() : Expression(ETan) {
}

bool Tan::isComplete() const {
    return (this->arg!=nullptr);
}

void Tan::traverse(Visitor& visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}


