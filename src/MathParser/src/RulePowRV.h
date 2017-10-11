/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RulePowRV.h
 * 
 * Grammar rule to handle exponentation operation for right hand operand (interface definition).
 * 
 * @since 16.08.2017
 * @author agor
 */

#ifndef RULEPOWRV_H
#define RULEPOWRV_H

#include "RuleOperations.h"

class Pow;

class RulePowRV : public RuleOperations<Pow, true> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEPOWRV_H */

