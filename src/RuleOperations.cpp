/**
 * @file   RuleOperations.cpp
 * 
 * @brief Implamentation of RuleOperations.
 * 
 * @since 15.08.2017
 * @author agor
 */

#include "RuleOperations.h"

RuleOperations::RuleOperations(bool isRightHand, ExpressionType operationType) : isRightHand(isRightHand), operationType(operationType) {}


bool RuleOperations::apply(ParserStack& stack, const Token& lookAheadToken) const throw (ParsingException) {
    return execute(stack, lookAheadToken);
}

bool RuleOperations::applyRuleWrapper(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
    if((*op)->type != this->operationType){
        return false;
    }
    
    // don't apply rule if operation of the left side is incomplete 
    if (!(*arg)->isComplete()) {
        return false;
    }

    // the operation on this position is already completed
    // for instance in case -(a+b) we will have stack "SubE Sum"
    // just skip it
    if ((*op)->isComplete()) {
        return false;
    }

    return (this->applyRule(op, arg, stack));
}

bool RuleOperations::execute(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        // check the priority of operation if priority is low, then skip rule
        // @TODO it is actually not a proper place for this check. At lest it should be done for the right expression (for the expected operation).
        if (next(nextItem) == stack.end() && hasPriority(this->operationType, lookAheadToken)) {
            continue;
        }

        if (this->isRightHand) {
            if (applyRuleWrapper(item, nextItem, stack)) {
                return true;
            }
        } else {
            if (applyRuleWrapper(nextItem, item, stack)) {
                return true;
            }
        }
    }

    return false;
}
