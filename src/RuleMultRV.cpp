/**
 * @file   RuleMultRV.cpp
 * 
 * Grammar rule to handle multiplication operation for the right hand operand.
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleMultRV.h"
#include "Mult.h"

bool RuleMultRV::apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        if ((*item)->type != EMult) {
            continue;
        }

        if (!(*nextItem)->isComplete()) {
            continue;
            // @TODO check whether it is appropriate to consider this case as exception
            //THROW(ParsingException, "Incomplete expression on the right side of '*'.", to_string(stack) + "; at symbol '" + lookAheadToken.value + "'");
        }

        // if the left side is empty 
        if (dynamic_pointer_cast<Mult>(*item)->lArg == nullptr) {
            THROW(ParsingException, "No operand on the left side of '*'.", to_string(stack) + "; at symbol '" + lookAheadToken.value + "'");
        }

        // see Grammar rule #26
        dynamic_pointer_cast<Mult>(*item)->rArg = *nextItem;
        stack.erase(nextItem);

        return true;
    }

    return false;
}