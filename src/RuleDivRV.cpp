/**
 * @file   RuleDivRV.cpp
 * 
 * Grammar rule to handle division operation for the right hand operand.
 * 
 * @since 15.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleDivRV.h"

bool RuleDivRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // if the left side is empty 
    if (SPointerCast<Div>(*op)->lArg == nullptr) {
        THROW(ParsingException, "No operand on the left side of '/'.", to_string(stack));
    }

    // see Grammar rule #28
    SPointerCast<Div>(*op)->rArg = *arg;
    stack.erase(arg);

    return true;
}