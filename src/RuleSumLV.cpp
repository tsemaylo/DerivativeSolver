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
	list<shared_ptr<Expression>>::iterator end=stack.end();
	
	while(item!=end){
		list<shared_ptr<Expression>>::iterator prevItem=item;
		++item;
		
		if((*item)->type == ESum){
			// ok we found "+" opeartor
			// then the left operand comes to + operationand item is removed from the stack
			
			// @TODO  if operation of the left side is incomplete then 
			// throw a parsing exception
			
			// @TODO check also brackets
			
			// the expression on the left side is correct
			// initialize l-side argument
			dynamic_cast<Sum *>((*item).get())->lArg=(*prevItem);
			// reduce the stack
			stack.erase(prevItem);
			
			return true;
		}
	}

	return false;
}
