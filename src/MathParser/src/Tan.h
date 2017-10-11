/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Tan.h
 * 
 * Definition of Tan class.
 * 
 * @author  agor
 * @since   22.08.2017
 */

#ifndef TAN_H
#define TAN_H

#include "Expression.h"

/**
 * The Expression class representing tangent function.
 */
class Tan : public Expression, public EnableSPointerFromThis<Tan>{
public:
    PExpression arg;
    
    Tan();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Tan> PTan;
typedef SPointer<const Tan> PConstTan;

#endif /* TAN_H */

