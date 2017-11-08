/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleSubRV.cpp
 * 
 * Grammar rule to handle SUBTRACTION operation for right hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RuleSubRV.h"
#include "Sub.h"
#include "Mult.h"
#include "Constant.h"
#include "ExpressionFactory.h"

bool RuleSubRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) {
        // if the left side is empty 
        // see Grammar rule #34
        if (SPointerCast<Sub>(*op)->lArg == nullptr) {
            // assuming the negation instead of subtraction 
            // replacing subtraction with multiplication with -1
            PMult mult = createMult(createConstant(-1.0), *arg);

            stack.insert(op, mult);
            stack.erase(op);
            stack.erase(arg);
            return true;
        }

        // see Grammar rule #33
        SPointerCast<Sub>(*op)->rArg = *arg;
        stack.erase(arg);
        return true;
}
