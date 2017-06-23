/**
 * @file   RuleSumRV.cpp
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "RuleSumRV.h"
#include "Function.h"

bool RuleSumRV::apply(list<unique_ptr<Expression>> &stack) const throw(ParsingException) {
	// search for the patterns
	
	// Function(L+) Expression -> Function(L+R)
	list<unique_ptr<Expression>>::iterator item=stack.begin();
	list<unique_ptr<Expression>>::iterator end=stack.end();
	
	while(item!=end){
		list<unique_ptr<Expression>>::iterator nextItem=item;
		++nextItem;
		
		if((*item)->getType() == EFunction && (*item)->getName()=="+"){
			// ok we found "+" opeartor
			
			if((*nextItem)->getType() == EFunction){ 
				// if operation on the right side is incomplete then 
				// throw a parsing exception
			}
			
			// @TODO check also brackets
			
			// the expression on the left side is correct
			// initialize l-side argument
			dynamic_cast<Function *>((*item).get())->addArgument(move(*nextItem));
			// reduce the stack
			stack.erase(nextItem);
			
			return true;
		}
		
		++item;
	}
	
	return false;
}
