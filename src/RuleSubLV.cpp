/**
 * @file   RuleSubLV.cpp
 * 
 * Grammar rule to handle SUBTRACTION operation for left hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleSubLV.h"
#include "Sub.h"

using namespace std;

bool RuleSubLV::apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        if ((*nextItem)->type != ESub) {
            continue;
        }

        if(next(nextItem) == stack.end() && hasPriority(ESub, lookAheadToken)){
            continue;
        }
        
        if ((*nextItem)->isComplete()) {
            continue;
        }

        if (!(*item)->isComplete()) {
            continue;
        }

        // see Grammar rule #32
        dynamic_pointer_cast<Sub>(*nextItem)->lArg = (*item);
        stack.erase(item);

        return true;
    }

    return false;
}
