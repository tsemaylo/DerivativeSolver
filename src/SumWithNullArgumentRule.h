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

#include "OptimizationRule.h"

#include <Sum.h>
#include <TraverseException.h>

class SumWithNullArgumentRule : public OptimizationRule {
public:
    SumWithNullArgumentRule(PSum _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* SUMWITHNULLARGUMENTRULE_H */

