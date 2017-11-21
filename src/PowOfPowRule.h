/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     PowOfPowRule.h
 * 
 * Definition of the PowOfPowRule class.
 * 
 * @author   agor
 * @since 16.11.2017
 */

#ifndef POWOFPOWRULE_H
#define POWOFPOWRULE_H

#include "OptimizationRule.tpp"
#include <Pow.h>
#include <TraverseException.h>

/**
 * The optimization for exponentiation expressions taken from other exponentiations.
 * 
 * Optimization patterns are: \n
 * - (x^m)^n = x^mn \n
 * - (1/x^n)^m = (x^-n)^m = x^-mn \n
 */
class PowOfPowRule : public OptimizationRule<PPow> {
public:
    PowOfPowRule(PPow _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* POWOFPOWRULE_H */

