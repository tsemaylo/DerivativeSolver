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
    return iterateStack(stack, lookAheadToken);
}

bool RuleOperations::applyRuleWrapper(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
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

bool RuleOperations::iterateStack(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        ParserStack::iterator op=nextItem;
        ParserStack::iterator arg=item;
        if(this->isRightHand) {
            op=item;
            arg=nextItem;
        }
        
        // proceed only with elemants of the considered type 
        // (for example process only Sum expressions if it is summation rule)
        if ((*op)->type != this->operationType) {
            continue;
        }
        
        // check the priority of operation if priority is low, then skip rule
        if (next(nextItem) == stack.end() && hasPriority(this->operationType, lookAheadToken)) {
            continue;
        }
        
        if (applyRuleWrapper(op, arg, stack)) {
            return true;
        }
    }

    return false;
}
