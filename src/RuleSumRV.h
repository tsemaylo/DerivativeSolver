/**
 * @file   RuleSumRV.h
 * 
 * Grammar rule to handle summation operation (Right hand operand).
 * 
 * @since 22.06.2017
 * @author agor
 */

#ifndef RULESUMRV_H
#define	RULESUMRV_H

#include "Rule.h"

class RuleSumRV : public Rule
{
	bool apply(list<unique_ptr<Expression>> &stack) const throw(ParsingException) final;
};

#endif	/* RULESUMRV_H */

