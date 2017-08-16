/**
 * @file    Pow.h
 * 
 * The definition of Pow interface.
 * 
 * @author  agor
 * @since 16.08.2017
 */

#ifndef POW_H
#define POW_H

#include "memory"
#include "Expression.h"

/**
 * Class represint the element of syntax tree responsible for exponentation operation.
 */
class Pow : public Expression, public enable_shared_from_this<Pow>  {
public:
    shared_ptr<Expression> lArg;
    shared_ptr<Expression> rArg;
    
    Pow();
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

#endif /* POW_H */

