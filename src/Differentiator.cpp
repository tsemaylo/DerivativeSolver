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

Differentiator::~Differentiator() {
	// TODO Auto-generated destructor stub
}

Expression *Differentiator::solve(const Constant &expr) const
{
	if(expr.getName().empty())
	{
		// log an warning
		//... i simply dunno what to do with expr, since it is not neaded in this case
		// but must be represented in interface
	}
	Constant *res=new Constant("0");
	return res;
}

Expression *Differentiator::solve(const Variable &expr) const
{
	if(expr.getName()==this->variable)
	{
		return new Constant("1");
	}

	return new Constant("0");
}

Expression *Differentiator::solve(const Function &expr) const
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
	Constant *res=new Constant("0");
	return res;
}
