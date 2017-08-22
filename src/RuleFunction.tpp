/**
 * @file RuleFunction.tpp
 * 
 * The implementation of RuleFunction.
 * 
 * @author  agor
 * @since 21.08.2017
 */


#include "bootstrap.h"
#include "RuleFunction.h"
#include "Sum.h"

template <class Function>
bool RuleFunction<Function>::apply(ParserStack& stack, const Token& ) const throw(ParsingException){
    ParserStack::iterator funcIt = stack.begin();
    ParserStack::iterator argIt = stack.begin();
    ++argIt;

    Function dummyFunction;
    for (; argIt != stack.end(); ++funcIt, ++argIt) {

        // search only the given funtion
        if((*funcIt)->type != dummyFunction.type){
            continue;
        }
        
        // ignoring already completed functions
        if((*funcIt)->isComplete()){
            continue;
        }

        // argument must be completed
        // ignoring already completed functions
        if(!(*argIt)->isComplete()){
            continue;
        }
        
        // assigning the argument and reducing the stack
        dynamic_pointer_cast<Function>(*funcIt)->arg=(*argIt);
        stack.erase(argIt);
        
        return true;
    }

    return false;
}