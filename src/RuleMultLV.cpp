/**
 * @file   RuleMultLV.cpp
 * 
 * Grammar rule to handle multiplication operation for left hand operand (implementation).
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleMultLV.h"
#include "Mult.h"

#include "iostream"

using namespace std;

bool RuleMultLV::apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        if ((*nextItem)->type != EMult) {
            continue;
        }

        if (!(*item)->isComplete()) {
            // @TODO has to be decided how to be with uncertainity in arguments
            cout << lookAheadToken.value;
            continue;
            
//            THROW(ParsingException, "Incomplete expression on the left side of '*'.", to_string(stack) + "; at symbol '" + lookAheadToken.value + "'");
        }

        if ((*nextItem)->isComplete()) {
            continue;
        }

        // Grammar rule #25
        dynamic_pointer_cast<Mult>(*nextItem)->lArg = (*item);
        stack.erase(item);

        return true;
    }

    return false;
}
