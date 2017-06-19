/** 
 * @file   Visitor.h
 * 
 * @brief Generic visitor interface.
 *
 * @since 12.06.2017
 * @author agor
 */

#ifndef VISITOR_H
#define	VISITOR_H

#include "Constant.h"
#include "Variable.h"
#include "Function.h"

/**
 * Interface for different visitors used to traverse the syntax tree (subtypes of Expression).
 */
class Visitor
{
public:	
	virtual void visit(const Constant &expr) = 0;
	virtual void visit(const Variable &expr) = 0;
	virtual void visit(const Function &expr) = 0;
};

#endif	/* VISITOR_H */

