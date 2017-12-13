/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleMultLV.cpp
 * 
 * Grammar rule to handle multiplication operation for left hand operand (implementation).
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RuleMultLV.h"
#include "Mult.h"

bool RuleMultLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    if(SPointerCast<Mult>(*op)->lArg != nullptr){
        return false;
    }
        
    // Grammar rule #25
    SPointerCast<Mult>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


