/**
 * @file    Pow.h
 * 
 * The implementation of Pow class.
 * 
 * @author  agor
 * @since 16.08.2017
 */

#include "Pow.h"
#include "Visitor.h"

Pow::Pow() : Expression(EPow){
}

void Pow::traverse(Visitor &visitor) const throw(TraverseException) {
    visitor.visit(shared_from_this());
}

bool Pow::isComplete() const {
    return (this->lArg != nullptr && this->rArg != nullptr);
}
