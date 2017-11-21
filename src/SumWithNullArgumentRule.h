/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumWithNullArgumentRule.h
 * 
 * Implementation of optimization rule to remove zeroes from the arguments of summation
 * 
 * @author agor
 * @since 28.09.2017
 */

#ifndef SUMWITHNULLARGUMENTRULE_H
#define SUMWITHNULLARGUMENTRULE_H

#include "OptimizationRule.tpp"

#include <Sum.h>
#include <TraverseException.h>

class SumWithNullArgumentRule : public OptimizationRule<PSum> {
public:
    SumWithNullArgumentRule(PSum _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* SUMWITHNULLARGUMENTRULE_H */

