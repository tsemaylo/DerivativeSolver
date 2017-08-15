/**
 * @file   RuleMultLV.h
 * 
 * Grammar rule to handle multiplication operation for left hand operand (definition).
 * 
 * @since 14.08.2017
 * @author agor
 */

#ifndef RULEMULTLV_H
#define RULEMULTLV_H

#include "RuleOperations.h"

using namespace std;

class RuleMultLV : public RuleOperations {
public:
    RuleMultLV();
    
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEMULTLV_H */

