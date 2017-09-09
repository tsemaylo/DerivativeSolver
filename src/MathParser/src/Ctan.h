/**
 * @file    Ctan.h
 * 
 * Definition of Ctan class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#ifndef CTAN_H
#define CTAN_H

#include "Expression.h"

/**
 * The derivative of Expression class representing the co-tangent function.
 */
class Ctan : public Expression, public EnableSPointerFromThis<Ctan>{
public:
    SPointer<Expression> arg;
    
    Ctan();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Ctan> PCtan;
typedef SPointer<const Ctan> PConstCtan;

#endif /* CTAN_H */

