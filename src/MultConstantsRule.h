/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     MultConstantsRule.h
 * 
 * Definition of the  MultConstantsRule class.
 * 
 * @author   agor
 * @since 10.11.2017
 */

#ifndef MULTCONSTANTSRULE_H
#define MULTCONSTANTSRULE_H

#include "OptimizationRule.h"

#include <Mult.h>

/**
 * The rule is intended to optimize the multiplication of/with constants.
 * 
 * The following cases are considered: \n
 * - A * B, where A and B are Constant's \n
 * - 0 * Expression =  0 \n
 * - 1 * Expression = Expression
 */
class MultConstantsRule : public OptimizationRule {
public:
    MultConstantsRule(PMult _expression);

    bool apply() throw (TraverseException) final;
};

#endif /* MULTCONSTANTSRULE_H */

