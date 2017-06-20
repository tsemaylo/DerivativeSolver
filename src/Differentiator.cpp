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
	if(expr.getName().empty())
	{
		// log an warning
		//... i simply dunno what to do with expr, since it is not neaded in this case
		// but must be represented in interface
	}
	this->result=new Constant("0");
}

void Differentiator::visit(const Variable &expr)  throw(TraverseException)
{
	if(expr.getName()==this->variable)
	{
		this->result=new Constant("1");
	}

	this->result=new Constant("0");
}

void Differentiator::visit(const Function &expr)  throw(TraverseException)
{
	if(expr.getName().empty())
	{
		// log an warning
		//... i simply dunno what to do with expr, since it is not neaded in this case
		// but must be represented in interface
	}

	if("+" == expr.getName())
	{
		/// @TODO
	}


	/// @TODO NYI
	// so far returning 0
	this->result=new Constant("0");
}

Expression* Differentiator::getLastVisitResult() const {
	return this->result;
}

void Differentiator::setLastVisitResult(Expression* result) {
	this->result=result;
}

