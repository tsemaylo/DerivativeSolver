/**
 * @file   RuleSubRV.h
 * 
 * Grammar rule to handle SUBTRACTION operation for right hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#ifndef RULESUBRV_H
#define RULESUBRV_H

#include "RuleOperations.h"
#include "Sub.h"

class RuleSubRV : public RuleOperations<Sub, true> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) final;
};

#endif /* RULESUBRV_H */

