/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleNoSignMult.cpp
 * 
 * The implementation of RuleNoSignMult.
 * 
 * @author  agor
 * @since 12.12.2017
 */

#include "RuleNoSignMult.h"
#include "ExpressionFactory.h"

bool RuleNoSignMult::apply(ParserStack& stack, const Token& lookAheadToken) const  throw(ParsingException) {
    ParserStack::iterator exprLeftIt = stack.begin();
    ParserStack::iterator exprRightIt = stack.begin();
    ++exprRightIt;

    for (; exprRightIt != stack.end(); ++exprLeftIt, ++exprRightIt) {
        
        // check the priority of operation if priority is low, then skip rule
        if (next(exprRightIt) == stack.end() && hasPriority<Mult>(lookAheadToken)) {
            return false;
        }
        
        // Grammar rules: #35
        
        if(!(*exprLeftIt)->isComplete() || !(*exprRightIt)->isComplete()){
            continue;
        }
 
        // both expression are completed 
        // pack them into Mult
        
        PMult mult = createMult(*exprLeftIt, *exprRightIt);

        stack.insert(exprLeftIt, mult);
        stack.erase(exprLeftIt);
        stack.erase(exprRightIt);

        return true;
    }

    return false;
}

