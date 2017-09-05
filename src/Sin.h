/**
 * @file    Sin.h
 * 
 * Definition of Sin class.
 * 
 * @author  agor
 * @since   16.08.2017
 */

#ifndef SIN_H
#define SIN_H

#include "Expression.h"

/**
 * The derivative of Expression class representing the cosine function.
 */
class Sin : public Expression, public enable_shared_from_this<Sin>{
public:
    PExpression arg;
    
    Sin();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Sin> PSin;
typedef SPointer<const Sin> PConstSin;

#endif /* SIN_H */

