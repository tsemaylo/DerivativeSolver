/**
 * @file   RuleSubLV.h
 * 
 * Grammar rule to handle SUBTRACTION operation for left hand operand.
 * 
 * @since 11.08.2017
 * @author agor
 */

#ifndef RULESUBLV_H
#define	RULESUBLV_H

#include "Rule.h"

using namespace std;

class RuleSubLV : public Rule
{
public:
	bool apply(ParserStack &stack) const throw(ParsingException) final;
};

#endif	/* RULESUBLV_H */

