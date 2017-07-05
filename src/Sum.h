/**
 * @file   Sum.h
 * 
 * Abstraction for expression for summation operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef SUM_H
#define	SUM_H

#include <memory>
#include "Expression.h"

class Sum : public Expression
{
public:
	unique_ptr<Expression> lArg;
	unique_ptr<Expression> rArg;

	Sum();
	
	void traverse(Visitor & ) const throw(TraverseException) final;
};

#endif	/* SUM_H */

