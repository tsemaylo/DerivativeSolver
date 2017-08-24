/**
 * @file   RuleSubRV.cpp
 * 
 * Grammar rule to handle SUBTRACTION operation for right hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleSubRV.h"
#include "Mult.h"
#include "Constant.h"

bool RuleSubRV::applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack& stack) const throw(ParsingException) {
        // if the left side is empty 
        // see Grammar rule #34
        if (dynamic_pointer_cast<Sub>(*op)->lArg == nullptr) {
            // assuming the negation instead of subtraction 
            // replacing subtraction with multiplication with -1
            shared_ptr<Mult> mult = make_shared<Mult>();
            mult->lArg = make_shared<Constant>("-1");
            mult->rArg = *arg;

            stack.insert(op, mult);
            stack.erase(op);
            stack.erase(arg);
            return true;
        }

        // see Grammar rule #33
        dynamic_pointer_cast<Sub>(*op)->rArg = *arg;
        stack.erase(arg);
        return true;
}
