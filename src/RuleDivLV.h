/**
 * @file   RuleDivLV.h
 * 
 * Grammar rule to handle division operation for left hand operand (definition).
 * 
 * @since 15.08.2017
 * @author agor
 */

#ifndef RULEDIVLV_H
#define RULEDIVLV_H

#include "RuleOperations.h"
#include "Div.h"

using namespace std;

class RuleDivLV : public RuleOperations<Div, false> {    
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEDIVLV_H */

