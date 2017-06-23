/**
 * @file   Rule.h
 * 
 * @brief Interface for syntax parsing rules.
 * 
 * @since 01.06.2017
 * @author agor
 */

#ifndef RULE_H
#define	RULE_H

#include <list>
#include <memory>
#include "Expression.h"
#include "ParsingException.h"

using namespace std;

/**
 * Represents the interface for any possible parsing rule.
 */
class Rule{
public:
	virtual bool apply(list<unique_ptr<Expression>> &stack) const throw(ParsingException) = 0;
};

#endif	/* RULE_H */

