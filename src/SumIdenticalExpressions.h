/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumIdenticalExpressions.h
 * 
 * Definition of SumIdenticalExpressions class.
 * 
 * @author agor
 * @since 06.11.2017
 */

#ifndef SUMIDENTICALEXPRESSIONS_H
#define SUMIDENTICALEXPRESSIONS_H

#include "OptimizationRule.h"

#include <Sum.h>
#include <TraverseException.h>
/**
 * The optimization rule to convert the expression like
 *   N*exp + M*exp 
 * to
 *   (N + M)*exp
 * where N and M are Constant s
 */
class SumIdenticalExpressions : public OptimizationRule {
public:
    SumIdenticalExpressions(PSum _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* SUMIDENTICALEXPRESSIONS_H */

