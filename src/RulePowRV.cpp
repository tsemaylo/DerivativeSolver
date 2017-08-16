/**
 * @file   RulePowRV.cpp
 * 
 * Grammar rule to handle exponentation operation for the right hand operand.
 * 
 * @since 16.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RulePowRV.h"
#include "Pow.h"

RulePowRV::RulePowRV() : RuleOperations(true, EPow) {
}

bool RulePowRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    if (dynamic_pointer_cast<Pow>(*op)->lArg == nullptr) {
        THROW(ParsingException, "No operand on the left side of '^'.", to_string(stack));
    }

    // see Grammar rule #24
    dynamic_pointer_cast<Pow>(*op)->rArg = *arg;
    stack.erase(arg);

    return true;
}