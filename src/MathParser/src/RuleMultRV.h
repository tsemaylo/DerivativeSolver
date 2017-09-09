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

#include "RuleOperations.h"

class Mult;

class RuleMultRV : public RuleOperations<Mult, true> {
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEMULTRV_H */

