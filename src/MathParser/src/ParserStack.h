/**
 * @file   ParserStack.h
 * 
 * @brief  The data type stack of terminals and non-terminals used by parser and its rules.
 * 
 * @since 26.07.2017
 * @author agor
 */

#ifndef PARSERSTACK_H
#define	PARSERSTACK_H
	
#include <list>
#include <string>
#include "Expression.h"	

class ParserStack : public std::list<PExpression>{};

std::string to_string(const ParserStack &val);
std::string to_string(ParserStack::const_iterator start, ParserStack::const_iterator end);

#endif	/* PARSERSTACK_H */
