/**
 * @file   RuleMultRV.h
 * 
 * Grammar rule to handle multiplication operation for right hand operand (interface definition).
 * 
 * @since 14.08.2017
 * @author agor
 */

#ifndef RULEMULTRV_H
#define RULEMULTRV_H

#include "Rule.h"

class RuleMultRV : public Rule {
public:
    bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) final;
};

#endif /* RULEMULTRV_H */

