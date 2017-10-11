/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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

#include "Expression.h"

/**
 * Class represint the element of syntax tree responsible for exponentation operation.
 */
class Pow : public Expression, public EnableSPointerFromThis<Pow>  {
public:
    PExpression lArg;
    PExpression rArg;
    
    Pow();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Pow> PPow;
typedef SPointer<const Pow> PConstPow;

#endif /* POW_H */

