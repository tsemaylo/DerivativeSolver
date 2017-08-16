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

class RulePowRV : public RuleOperations {
public:
    RulePowRV();
    
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEPOWRV_H */

