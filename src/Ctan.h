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

#include <memory>
#include "Expression.h"

/**
 * The derivative of Expression class representing the co-tangent function.
 */
class Ctan : public Expression, public enable_shared_from_this<Ctan>{
public:
    shared_ptr<Expression> arg;
    
    Ctan();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

typedef shared_ptr<Ctan> PCtan;

#endif /* CTAN_H */

