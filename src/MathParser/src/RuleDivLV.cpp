/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleDivLV.cpp
 * 
 * Grammar rule to handle division operation for left hand operand (implementation).
 * 
 * @since 15.08.2017
 * @author agor
 */

#include "ExceptionThrower.h"
#include "RuleDivLV.h"

#include "Div.h"
#include "ParsingException.h"

bool RuleDivLV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    if(SPointerCast<Div>(*op)->lArg != nullptr){
        return false;
    }
        
    // Grammar rule #27
    SPointerCast<Div>(*op)->lArg = *arg;
    stack.erase(arg);

    return true;
}


