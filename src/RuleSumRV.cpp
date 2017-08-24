/**
 * @file   RuleSumRV.cpp
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleSumRV.h"

bool RuleSumRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw (ParsingException) {
    // if the left side is empty 
    // see Grammar rule #31
    if (dynamic_pointer_cast<Sum>(*op)->lArg == nullptr) {
        // remove summation and left complete expression on the right side as is
        stack.erase(op);
        return true;
    }

    // the expression on the left side is correct
    // initialize r-side argument
    // see Grammar rule #30
    dynamic_pointer_cast<Sum>(*op)->rArg = *arg;
    // reduce the stack
    stack.erase(arg);
    return true;
}
