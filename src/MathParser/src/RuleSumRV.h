/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleSumRV.h
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#ifndef RULESUMRV_H
#define RULESUMRV_H

#include "RuleOperations.h"

class Sum;

class RuleSumRV : public RuleOperations<Sum, true> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) final;
};

#endif /* RULESUMRV_H */

