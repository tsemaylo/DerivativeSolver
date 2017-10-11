/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

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

#include "Expression.h"

/**
 * The derivative of Expression class representing the cosine function.
 */
class Cos : public Expression, public EnableSPointerFromThis<Cos>{
public:
    SPointer<Expression> arg;
    
    Cos();
    
    bool isComplete() const final;
    void traverse(Visitor&) const throw(TraverseException) final;
};

// shortcuts for pointers
typedef SPointer<Cos> PCos;
typedef SPointer<const Cos> PConstCos;

#endif /* COS_H */

