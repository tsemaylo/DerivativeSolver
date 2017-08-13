/**
 * @file   RuleSumRV.cpp
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "bootstrap.h"
#include "RuleSumRV.h"
#include "Sum.h"

bool RuleSumRV::apply(ParserStack &stack, const Token &lookAheadToken) const throw(ParsingException) {
	// search for the patterns
	
	ParserStack::iterator item=stack.begin();
	ParserStack::iterator nextItem=stack.begin();
	++nextItem;
	
	for(;nextItem!=stack.end();++item, ++nextItem){
		if((*item)->type != ESum){
			continue;
		}
		
		// ok we found "+" opeartor
			
		// if operation on the right side is incomplete then 
		// throw a parsing exception
		if(!(*nextItem)->isComplete()){
			THROW(ParsingException, "Incomplete expression on the right side of '+'.", to_string(stack)+ "; at symbol '" + lookAheadToken.value + "'");
		}
		
		// if the left side is empty 
		// see Grammar rule #31
		if(dynamic_pointer_cast<Sum>(*item)->lArg==nullptr){
			// remove summation and left complete expression on the right side as is
			stack.erase(item);
			return true;
		}
		
		// the expression on the left side is correct
		// initialize r-side argument
		// see Grammar rule #30
		dynamic_pointer_cast<Sum>(*item)->rArg = *nextItem;
		// reduce the stack
		stack.erase(nextItem);
		return true;
	}
	
	return false;
}
