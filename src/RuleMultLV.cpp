/**
 * @file   RuleMultLV.cpp
 * 
 * Grammar rule to handle multiplication operation for left hand operand (implementation).
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleMultLV.h"
#include "Mult.h"

using namespace std;

RuleMultLV::RuleMultLV() : RuleOperations(false, EMult){}

bool RuleMultLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // Grammar rule #25
    dynamic_pointer_cast<Mult>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


