/**
 * @file    Ln.h
 * 
 * Definition of Ln class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#ifndef LN_H
#define LN_H

#include "Expression.h"

/**
 * The derivative of Expression class representing natural logarithm function.
 */
class Ln : public Expression, public enable_shared_from_this<Ln>{
public:
    PExpression arg;
    
    Ln();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Ln> PLn;
typedef SPointer<const Ln> PConstLn;

#endif /* LN_H */

