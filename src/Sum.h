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

class Sum : public Expression, public enable_shared_from_this<Sum>
{
public:
	shared_ptr<Expression> lArg;
	shared_ptr<Expression> rArg;

	Sum();
	
	void traverse(Visitor & ) const throw(TraverseException) final;
	
	bool isComplete() const final;
};

#endif	/* SUM_H */

