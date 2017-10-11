/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RulePowRV.cpp
 * 
 * Grammar rule to handle exponentation operation for the right hand operand.
 * 
 * @since 16.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RulePowRV.h"
#include "Pow.h"

bool RulePowRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    if (SPointerCast<Pow>(*op)->lArg == nullptr) {
        THROW(ParsingException, "No operand on the left side of '^'.", to_string(stack));
    }

    // see Grammar rule #24
    SPointerCast<Pow>(*op)->rArg = *arg;
    stack.erase(arg);

    return true;
}