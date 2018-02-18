/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleOperations.tpp
 * 
 * @brief Implamentation of RuleOperations.
 * 
 * @since 15.08.2017
 * @author agor
 */

#include "ParsingException.h"

template <class OperationClass, bool isRightHand>
bool RuleOperations<OperationClass, isRightHand>::apply(ParserStack& stack, const Token& lookAheadToken) const throw (ParsingException) {
    return iterateStack(stack, lookAheadToken);
}

template <class OperationClass, bool isRightHand>
bool RuleOperations<OperationClass, isRightHand>::applyRuleWrapper(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) {
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

template<class OperationClass, bool isRightHand>
bool RuleOperations<OperationClass, isRightHand>::iterateStack(ParserStack& stack, const Token& lookAheadToken) const throw (ParsingException) {
    ParserStack::iterator item = stack.begin();
    ParserStack::iterator nextItem = stack.begin();
    ++nextItem;

    for (; nextItem != stack.end(); ++item, ++nextItem) {
        ParserStack::iterator op = nextItem;
        ParserStack::iterator arg = item;
        if (isRightHand) {
            op = item;
            arg = nextItem;
        }

        // proceed only with elements of the considered type 
        // (for example process only Sum expressions if it is summation rule)
        if (!isTypeOf<OperationClass>(*op)) {
            continue;
        }

        // check the priority of operation if priority is low, then skip rule
        if (next(nextItem) == stack.end() && hasPriority<OperationClass>(lookAheadToken)) {
            continue;
        }

        if (applyRuleWrapper(op, arg, stack)) {
            return true;
        }
    }

    return false;
}
