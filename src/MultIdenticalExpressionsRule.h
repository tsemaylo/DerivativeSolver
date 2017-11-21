/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultIdenticalExpressionsRule.h
 * 
 * Definition of the  MultIdenticalExpressionsRule class.
 * 
 * @author   agor
 * @since 14.11.2017
 */

#ifndef MULTIDENTICALEXPRESSIONSRULE_H
#define MULTIDENTICALEXPRESSIONSRULE_H

#include "OptimizationRule.tpp"

#include <Mult.h>
#include <TraverseException.h>

/**
 * The optimization rule to find the product of two identical expressions.
 * 
 * The tries to mathe the given Mult with the following pattern:
 *   A*Expression^M * B*Expression^N
 * and reduce it to the form: AB*Expression^(M+N)
 */
class MultIdenticalExpressionsRule : public OptimizationRule<PMult> {
public:
    MultIdenticalExpressionsRule(PMult _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* MULTIDENTICALEXPRESSIONSRULE_H */

