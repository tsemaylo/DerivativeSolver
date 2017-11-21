/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file     PowConstantRule.h
 * 
 * Definition of the PowConstantRule class.
 * 
 * @author   agor
 * @since 16.11.2017
 */

#ifndef POWCONSTANTRULE_H
#define POWCONSTANTRULE_H

#include "OptimizationRule.tpp"
#include <TraverseException.h>
#include <Pow.h>

/**
 * The PowConstantRule calss is intended to optimize exponentiation expressions 
 * involving constants.
 * 
 * The folllowing cases are considered: \n
 *  A^B -> calculate results \n
 *  Expression ^ 0 = 1 \n
 *  Expression ^ 1 = Expression 
 */
class PowConstantRule : public OptimizationRule<PPow> {
public:
    PowConstantRule(PPow _expression);
    bool apply() throw (TraverseException) final;
};

#endif /* POWCONSTANTRULE_H */

