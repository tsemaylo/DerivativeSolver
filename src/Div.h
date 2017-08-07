/**
 * @file   Div.h
 * 
 * Abstraction for expression for division operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef DIV_H
#define	DIV_H

#include <memory>
#include "Expression.h"

class Div : public Expression
{
public:
	shared_ptr<Expression> lArg;
	shared_ptr<Expression> rArg;

	Div();
	
	void traverse(Visitor & ) const throw(TraverseException) final;
	
	bool isComplete() const final;
};

#endif	/* DIV_H */

