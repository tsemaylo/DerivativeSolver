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

#include "Rule.h"

using namespace std;

class RuleMultLV : public Rule {
public:
    bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) final;
};

#endif /* RULEMULTLV_H */

