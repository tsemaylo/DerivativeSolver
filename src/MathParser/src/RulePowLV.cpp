/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RulePowLV.cpp
 * 
 * Grammar rule to handle exponentation operation for left hand operand (implementation).
 * 
 * @since 16.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RulePowLV.h"
#include "Pow.h"

bool RulePowLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    // Grammar rule #23
    SPointerCast<Pow>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


