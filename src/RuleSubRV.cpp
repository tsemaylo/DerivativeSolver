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
#include "Sub.h"
#include "Mult.h"
#include "Constant.h"

bool RuleSubRV::apply(ParserStack &stack) const throw(ParsingException) {
	// search for the patterns
	
	ParserStack::iterator item=stack.begin();
	ParserStack::iterator nextItem=stack.begin();
	++nextItem;
	
	for(;nextItem!=stack.end();++item, ++nextItem){
		if((*item)->type != ESub){
			continue;
		}
		
		if(!(*nextItem)->isComplete()){
			THROW(ParsingException, "Incomplete expression on the right side of '-'.", to_string(stack));
		}
		
		// if the left side is empty 
		// see Grammar rule #34
		if(dynamic_pointer_cast<Sub>(*item)->lArg==nullptr){
			// assuming the negation instead of subtraction 
			// replacing subtraction with multiplication with -1
			shared_ptr<Mult> mult=make_shared<Mult>();
			mult->lArg=make_shared<Constant>("-1");
			mult->rArg=*nextItem;
			
			stack.insert(item, mult);
			stack.erase(item);
			stack.erase(nextItem);
			return true;
		}
		
		// see Grammar rule #33
		dynamic_pointer_cast<Sub>(*item)->rArg = *nextItem;
		stack.erase(nextItem);
		return true;
	}
	
	return false;
}
