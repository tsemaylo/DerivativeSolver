/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Exp.h
 * 
 * Definition of Exp class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#ifndef EXP_H
#define EXP_H

#include "Expression.h"

/**
 * The derivative of Expression class representing the exponential function of base e.
 */
class Exp : public Expression, public EnableSPointerFromThis<Exp>{
public:
    PExpression arg;
    
    Exp();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Exp> PExp;
typedef SPointer<const Exp> PConstExp;

#endif /* EXP_H */

