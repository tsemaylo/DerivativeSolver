/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     LnOfExpRule.h
 * 
 * Definition of the LnOfExpRule class.
 * 
 * @author   agor
 * @since 21.11.2017
 */

#ifndef LNOFEXPRULE_H
#define LNOFEXPRULE_H

#include <Ln.h>
#include <TraverseException.h>

#include "OptimizationRule.tpp"

/**
 * The optimization rule is intended to simplify the pattern: ln(exp(x)) = x.
 */
class LnOfExpRule : public OptimizationRule<PLn> {
public:
    LnOfExpRule(PLn _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* LNOFEXPRULE_H */

