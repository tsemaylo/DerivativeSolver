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

#include "Rule.h"

class RuleSubRV : public Rule {
public:
    bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) final;
};

#endif /* RULESUBRV_H */

