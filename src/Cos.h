/**
 * @file    Cos.h
 * 
 * Definition of Cos class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#ifndef COS_H
#define COS_H

#include <memory>
#include "Expression.h"

/**
 * The derivative of Expression class representing the cosine function.
 */
class Cos : public Expression, public enable_shared_from_this<Cos>{
public:
    shared_ptr<Expression> arg;
    
    Cos();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

typedef shared_ptr<Cos> PCos;

#endif /* COS_H */

