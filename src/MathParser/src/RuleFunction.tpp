/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleFunction.tpp
 * 
 * The implementation of RuleFunction.
 * 
 * @author  agor
 * @since 21.08.2017
 */

#include "ParsingException.h"

template <class Function>
bool RuleFunction<Function>::apply(ParserStack& stack, const Token& ) const throw(ParsingException){
    ParserStack::iterator funcIt = stack.begin();
    ParserStack::iterator argIt = stack.begin();
    ++argIt;

    for (; argIt != stack.end(); ++funcIt, ++argIt) {
        // search only the given funtion
        if(!isTypeOf<Function>((*funcIt))){
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
        // Grammar rules: #17-22
        SPointerCast<Function>(*funcIt)->arg=(*argIt);
        stack.erase(argIt);
        
        return true;
    }

    return false;
}