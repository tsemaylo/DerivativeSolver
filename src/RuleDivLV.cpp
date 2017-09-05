/**
 * @file   RuleDivLV.cpp
 * 
 * Grammar rule to handle division operation for left hand operand (implementation).
 * 
 * @since 15.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleDivLV.h"

using namespace std;

bool RuleDivLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // Grammar rule #27
    SPointerCast<Div>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


