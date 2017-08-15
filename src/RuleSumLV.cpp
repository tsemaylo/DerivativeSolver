/**
 * @file   RuleSumLV.cpp
 * 
 * Grammar rule to handle summation operation (left hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleSumLV.h"
#include "Sum.h"

using namespace std;

RuleSumLV::RuleSumLV() : RuleOperations(false, ESum) {
}

bool RuleSumLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw (ParsingException) {
    // the expression on the left side is correct
    // initialize l-side argument
    // see Grammar rule #29
    dynamic_pointer_cast<Sum>(*op)->lArg = (*arg);
    // reduce the stack
    stack.erase(arg);

    return true;
}
