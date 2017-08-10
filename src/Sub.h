/**
 * @file   Sub.h
 * 
 * Abstraction for expression for subtraction operation.
 * 
 * @since 04.07.2017
 * @author agor
 */

#ifndef SUB_H
#define	SUB_H

#include <memory>
#include "Expression.h"

class Sub : public Expression, public enable_shared_from_this<Sub> 
{
public:
	shared_ptr<Expression> lArg;
	shared_ptr<Expression> rArg;

	Sub();
	
	void traverse(Visitor & ) const throw(TraverseException) final;
	
	bool isComplete() const final;
};

#endif	/* SUB_H */

