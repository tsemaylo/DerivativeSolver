/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultNumeratorDenominatorRule.h
 * 
 * Definition of the  MultNumeratorDenominatorRule class.
 * 
 * @author   agor
 * @since 15.12.2017
 */

#ifndef MULTNUMERATORDENOMINATOR_H
#define MULTNUMERATORDENOMINATOR_H

#include "OptimizationRule.tpp"

#include <Mult.h>
#include <TraverseException.h>

/**
 * Optimization rule to reduce similar nummerator and denominator in cases:
 * ax^n*b/x^m => (a*b)*x^(n-m), if n > m
 * ax^n*b/x^m => (a*b)/x^(m-n), if m > n
 * 
 * a and b can be random expressions.
 */
class MultNumeratorDenominatorRule : public OptimizationRule<PMult>{
public:
    MultNumeratorDenominatorRule(PMult _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* MULTNUMERATORDENOMINATOR_H */

