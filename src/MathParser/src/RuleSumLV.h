/**
 * @file   RuleSumLV.h
 * 
 * Grammar rule to handle summation operation (Left hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#ifndef RULESUMLV_H
#define RULESUMLV_H

#include "RuleOperations.h"

class Sum;

class RuleSumLV : public RuleOperations<Sum, false> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) final;
};

#endif /* RULESUMLV_H */

