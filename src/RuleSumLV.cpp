/**
 * @file   RuleSumLV.cpp
 * 
 * Grammar rule to handle summation operation (left hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#include "RuleSumLV.h"
#include "Function.h"

using namespace std;

bool RuleSumLV::apply(list<unique_ptr<Expression>> &stack) const throw(ParsingException) {
	// search for the patterns
	
	// Expression Function(+) -> Function(L+)
	list<unique_ptr<Expression>>::iterator item=stack.begin();
	list<unique_ptr<Expression>>::iterator end=stack.end();
	
	while(item!=end){
		list<unique_ptr<Expression>>::iterator nextItem=item;
		++nextItem;
		
		if((*nextItem)->getType() == EFunction && (*nextItem)->getName()=="+"){
			// ok we found "+" opeartor
			// then the left operand comes to + operationand item is removed from the stack
			if((*item)->getType() == EFunction){ 
				// if operation of the left side is incomplete then 
				// throw a parsing exception
			}
			
			// @TODO check also brackets
			
			// the expression on the left side is correct
			// initialize l-side argument
			dynamic_cast<Function *>((*nextItem).get())->addArgument(move(*item));
			// reduce the stack
			stack.erase(item);
			
			return true;
		}
		
		++item;
	}

	return false;
}
