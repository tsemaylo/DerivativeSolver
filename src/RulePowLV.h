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
#include "Pow.h"

using namespace std;

class RulePowLV : public RuleOperations<Pow, false> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEPOWLV_H */

