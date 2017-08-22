/**
 * @file    Exp.cpp
 * 
 * Implemntation of Exp class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#include "Exp.h"
#include "Visitor.h"

Exp::Exp() : Expression(EExp) {
}

bool Exp::isComplete() const {
    return (this->arg!=nullptr);
}

void Exp::traverse(Visitor& visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}


