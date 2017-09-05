/**
 * @file   RuleMultRV.cpp
 * 
 * Grammar rule to handle multiplication operation for the right hand operand.
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleMultRV.h"

bool RuleMultRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // if the left side is empty 
    if (SPointerCast<Mult>(*op)->lArg == nullptr) {
        THROW(ParsingException, "No operand on the left side of '*'.", to_string(stack));
    }

    // see Grammar rule #26
    SPointerCast<Mult>(*op)->rArg = *arg;
    stack.erase(arg);

    return true;
}