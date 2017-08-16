/**
 * @file   RulePowLV.cpp
 * 
 * Grammar rule to handle exponentation operation for left hand operand (implementation).
 * 
 * @since 16.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RulePowLV.h"
#include "Pow.h"

using namespace std;

RulePowLV::RulePowLV() : RuleOperations(false, EPow){}

bool RulePowLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // Grammar rule #23
    dynamic_pointer_cast<Pow>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


