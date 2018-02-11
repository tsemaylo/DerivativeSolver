/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultWithNumeratorRule.h
 * 
 * Definition of the MultWithNumeratorRule class.
 * 
 * @author   agor
 * @since 21.01.2018
 */

#ifndef MULTWITHNUMERATORRULE_H
#define MULTWITHNUMERATORRULE_H

#include "OptimizationRule.tpp"

#include <TraverseException.h>
#include <Mult.h>

/**
 * Optimization rule to put multiplier from the leftside of division to the its numerator:
 * a*(b/c) => (ab)/c
 * 
 * a and b can be random expressions.
 */
class MultWithNumeratorRule : public OptimizationRule<PMult> {
public:
    MultWithNumeratorRule(PMult _expression);
    bool apply() throw(TraverseException) final;

private:

};

#endif /* MULTWITHNUMERATORRULE_H */

