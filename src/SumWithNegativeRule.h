/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumWithNegativeRule.h
 * 
 * Implementation of SumWithNegativeRule optimization rule.
 * 
 * @author agor
 * @since 11.02.2017
 */

#ifndef SUMWITHNEGATIVERULE_H
#define SUMWITHNEGATIVERULE_H

#include "OptimizationRule.tpp"

#include <Sum.h>
#include <TraverseException.h>

/**
 * The optimization rule is intended to simplify expressions of type:
 * 
 * a+(-1*b) => a-b
 * 
 * where a and b are random expressions.
 */
class SumWithNegativeRule : public OptimizationRule<PSum>{
public:
    SumWithNegativeRule(PSum _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* SUMWITHNEGATIVERULE_H */

