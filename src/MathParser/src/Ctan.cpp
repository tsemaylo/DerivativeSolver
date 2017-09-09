/**
 * @file    Ctan.cpp
 * 
 * Implemntation of Ctan class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#include "Ctan.h"
#include "Visitor.h"
#include "TraverseException.h"

Ctan::Ctan() : Expression(ECtan) {
}

bool Ctan::isComplete() const {
    return (this->arg!=nullptr);
}

void Ctan::traverse(Visitor& visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}