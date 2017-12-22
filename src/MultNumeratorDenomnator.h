/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultNumeratorDenomnator.h
 * 
 * Definition of the  MultNumeratorDenomnator class.
 * 
 * @author   agor
 * @since 15.12.2017
 */

#ifndef MULTNUMERATORDENOMNATOR_H
#define MULTNUMERATORDENOMNATOR_H

#include "OptimizationRule.tpp"

#include <Mult.h>
#include <TraverseException.h>

/**
 * Optimization rule to reduce similar nummerator and denominator in cases:
 * ax^n*b/x^m => a * x^(n-m) * b, if n > m
 * ax^n*b/x^m => a * b/x^(m-n), if m > n
 * 
 * a and b can be random expressions.
 */
class MultNumeratorDenomnator : public OptimizationRule<PMult>{
public:
    MultNumeratorDenomnator(PMult _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* MULTNUMERATORDENOMNATOR_H */

