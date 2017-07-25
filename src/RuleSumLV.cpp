/**
 * @file   RuleSumLV.cpp
 * 
 * Grammar rule to handle summation operation (left hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "RuleSumLV.h"
#include "Sum.h"

using namespace std;

bool RuleSumLV::apply(list<shared_ptr<Expression>> &stack) const throw(ParsingException) {
	// search for the patterns
	
	// Expression Function(+) -> Function(L+)	
	list<shared_ptr<Expression>>::iterator item=stack.begin();
	list<shared_ptr<Expression>>::iterator nextItem=stack.begin();
	++nextItem;
	
	// iterating through the "frame" of two items
	for( ;nextItem!=stack.end(); ++item, ++nextItem){		
		if((*nextItem)->type == ESum){
			// ok we found "+" opeartor
			// then the left operand comes to + operationand item is removed from the stack
			
			// @TODO  if operation of the left side is incomplete then 
			// throw a parsing exception
			
			// @TODO check also brackets
			
			// the expression on the left side is correct
			// initialize l-side argument
			dynamic_cast<Sum *>((*nextItem).get())->lArg=(*item);
			// reduce the stack
			stack.erase(item);
			
			return true;
		}
	}

	return false;
}
