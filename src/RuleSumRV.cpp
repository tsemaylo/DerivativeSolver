/**
 * @file   RuleSumRV.cpp
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "RuleSumRV.h"
#include "Sum.h"

bool RuleSumRV::apply(list<shared_ptr<Expression>> &stack) const throw(ParsingException) {
	// search for the patterns
	
	// Function(L+) Expression -> Function(L+R)
	list<shared_ptr<Expression>>::iterator item=stack.begin();
	list<shared_ptr<Expression>>::iterator end=stack.end();
	
	while(item!=end){
		list<shared_ptr<Expression>>::iterator nextItem=item;
		++nextItem;
		
		if((*item)->type == ESum){
			// ok we found "+" opeartor
			
			// @TODO if operation on the right side is incomplete then 
			// throw a parsing exception
			
			// @TODO check also brackets
			
			// the expression on the left side is correct
			// initialize l-side argument
			dynamic_cast<Sum *>((*item).get())->rArg = *nextItem;
			// reduce the stack
			stack.erase(nextItem);
			
			return true;
		}
		
		++item;
	}
	
	return false;
}
