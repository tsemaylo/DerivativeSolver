/**
 * @file   ParserStack.h
 * 
 * @brief  The data taype represents the stack of terminal and non-terminals used by parser and his rules.
 * 
 * @since 26.07.2017
 * @author agor
 */

#ifndef PARSERSTACK_H
#define	PARSERSTACK_H

#ifdef	__cplusplus
extern "C"
{
#endif
	
#include <list>
#include <memory>
#include "Expression.h"	

typedef	list<shared_ptr<Expression>>	ParserStack;


#ifdef	__cplusplus
}
#endif

#endif	/* PARSERSTACK_H */

