/**
 * @file   RuleSumLV.h
 * 
 * Grammar rule to handle summation operation (Left hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#ifndef RULESUMLV_H
#define	RULESUMLV_H

#include "Rule.h"

using namespace std;

class RuleSumLV : public Rule
{
public:
	bool apply(ParserStack &stack, const Token &lookAheadToken) const throw(ParsingException) final;
};

#endif	/* RULESUMLV_H */

