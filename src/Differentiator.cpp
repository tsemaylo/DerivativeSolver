/**
 * @file Differentiator.cpp
 *
 * @brief Implementation of the differentiation logic.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Differentiator.h"

Differentiator::Differentiator(string var) : variable(var){
}

void Differentiator::visit(const Constant &expr) throw(TraverseException)
{
	if(expr.value.empty())
	{
		// log an warning
		//... i simply dunno what to do with expr, since it is not neaded in this case
		// but must be represented in interface
	}
	this->result=new Constant("0");
}

void Differentiator::visit(const Variable &expr)  throw(TraverseException)
{
	if(expr.name == this->variable)
	{
		this->result=new Constant("1");
	}

	this->result=new Constant("0");
}

void Differentiator::visit(const Sum &expr)  throw(TraverseException)
{
	// here must be a long story with unique_ptr
//	Sum *difSummation=new Sum();
//	
//	expr.lArg->traverse(*this);
//	Expression *lArg=this->getLastVisitResult();
//	expr.lArg->traverse(*this);
//	Expression *rArg=this->getLastVisitResult();
//	
//	difSummation->lArg=lArg
//	difSummation->rArg=rArg;
	
	/// @TODO NYI
	// so far returning 0
	this->result=new Constant(to_string(expr.type));
}

void Differentiator::visit(const Sub &expr)  throw(TraverseException)
{
	/// @TODO s.a.
	/// @TODO NYI
	this->result=new Constant(to_string(expr.type));
}

void Differentiator::visit(const Div &expr)  throw(TraverseException)
{
	/// @TODO s.a.
	/// @TODO NYI
	this->result=new Constant(to_string(expr.type));
}

void Differentiator::visit(const Mult &expr)  throw(TraverseException)
{
	/// @TODO s.a.
	/// @TODO NYI
	this->result=new Constant(to_string(expr.type));
}

Expression* Differentiator::getLastVisitResult() const {
	return this->result;
}

void Differentiator::setLastVisitResult(Expression* result) {
	this->result=result;
}

