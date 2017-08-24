/**
 * @file   RuleDivRV.h
 * 
 * Grammar rule to handle division operation for right hand operand (interface definition).
 * 
 * @since 15.08.2017
 * @author agor
 */

#ifndef RULEDIVRV_H
#define RULEDIVRV_H

#include "RuleOperations.h"
#include "Div.h"

class RuleDivRV : public RuleOperations<Div, true> { 
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEDIVRV_H */

