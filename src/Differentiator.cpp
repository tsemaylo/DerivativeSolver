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

void Differentiator::visit(const shared_ptr<const Constant> expr) throw(TraverseException)
{
	if(expr->value.empty())
	{
		// log an warning
		//... i simply dunno what to do with expr, since it is not neaded in this case
		// but must be represented in interface
	}
	this->setLastVisitResult(make_shared<Constant>("0"));
}

void Differentiator::visit(const shared_ptr<const Variable> expr)  throw(TraverseException)
{
	if(expr->name == this->variable)
	{
		this->setLastVisitResult(make_shared<Constant>("1"));
	}

	this->setLastVisitResult(make_shared<Constant>("0"));
}

void Differentiator::visit(const shared_ptr<const Sum> expr)  throw(TraverseException)
{
	shared_ptr<Sum> difSummation=make_shared<Sum>();

	expr->lArg->traverse(*this);
	shared_ptr<Expression> lArg=this->getLastVisitResult();
	expr->rArg->traverse(*this);
	shared_ptr<Expression> rArg=this->getLastVisitResult();

	difSummation->lArg=lArg;
	difSummation->rArg=rArg;
	
	this->setLastVisitResult(difSummation);
}

void Differentiator::visit(const shared_ptr<const Sub> expr)  throw(TraverseException)
{
	shared_ptr<Sub> difSubtraction=make_shared<Sub>();

	expr->lArg->traverse(*this);
	shared_ptr<Expression> lArg=this->getLastVisitResult();
	expr->rArg->traverse(*this);
	shared_ptr<Expression> rArg=this->getLastVisitResult();

	difSubtraction->lArg=lArg;
	difSubtraction->rArg=rArg;
	
	this->setLastVisitResult(difSubtraction);
}

void Differentiator::visit(const shared_ptr<const Div> expr)  throw(TraverseException)
{
	/// @TODO s.a.
	/// @TODO NYI
	this->setLastVisitResult(make_shared<Constant>(to_string(expr->type)));
}

void Differentiator::visit(const shared_ptr<const Mult> expr)  throw(TraverseException)
{
	/// @TODO s.a.
	/// @TODO NYI
	this->setLastVisitResult(make_shared<Constant>(to_string(expr->type)));
}

shared_ptr<Expression> Differentiator::getLastVisitResult() const {
	return this->result;
}

void Differentiator::setLastVisitResult(shared_ptr<Expression> result) {
	this->result=result;
}

