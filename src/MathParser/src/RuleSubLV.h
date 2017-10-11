/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleSubLV.h
 * 
 * Grammar rule to handle SUBTRACTION operation for left hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#ifndef RULESUBLV_H
#define RULESUBLV_H

#include "RuleOperations.h"

class Sub;

class RuleSubLV : public RuleOperations<Sub, false> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) final;
};

#endif /* RULESUBLV_H */

