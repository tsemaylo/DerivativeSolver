/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RulePowLV.h
 * 
 * Grammar rule to handle exponentation operation for left hand operand (definition).
 * 
 * @since 16.08.2017
 * @author agor
 */

#ifndef RULEPOWLV_H
#define RULEPOWLV_H

#include "RuleOperations.h"

class Pow;

class RulePowLV : public RuleOperations<Pow, false> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEPOWLV_H */

