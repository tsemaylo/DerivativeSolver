/**
 * @file   RuleSubLV.cpp
 * 
 * Grammar rule to handle SUBTRACTION operation for left hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RuleSubLV.h"
#include "Sub.h"

bool RuleSubLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) {
    // see Grammar rule #32
    SPointerCast<Sub>(*op)->lArg = (*arg);
    stack.erase(arg);

    return true;
}
