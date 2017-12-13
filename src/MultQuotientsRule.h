/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultQuotientsRule.h
 * 
 * Definition of the MultQuotientsRule class.
 * 
 * @author   agor
 * @since 13.12.2017
 */

#ifndef MULTQUOTIENTSRULE_H
#define MULTQUOTIENTSRULE_H

#include "OptimizationRule.tpp"

#include <TraverseException.h>
#include <Mult.h>

/**
 * Optimization rule to optimize the following cases:
 *  - a*(b*x) => ab*x
 *  - a*(b/x) => ab/x
 * Also considering different combinations of arguments.
 */
class MultQuotientsRule : public OptimizationRule<PMult> {
public:
    MultQuotientsRule(PMult _expression);
    bool apply() throw(TraverseException) final;
};

#endif /* MULTQUOTIENTSRULE_H */

