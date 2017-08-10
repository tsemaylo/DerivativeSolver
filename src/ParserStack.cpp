/**
 * @file   ParserStack.cpp
 * 
 * @brief  The data type stack of terminals and non-terminals used by parser and his rules.
 * 
 * @since 09.08.2017
 * @author agor
 */

#include "ParserStack.h"
#include "StringGenerator.h"

#include <string>

string to_string(const ParserStack &stack){
	string out="";
	for(auto item : stack){
		StringGenerator stringGenerator;
		item->traverse(stringGenerator);
		out+=stringGenerator.getLastVisitResult();
	}
	return out;
}