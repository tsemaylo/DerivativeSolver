/**
 * \file Variable.cpp
 *
 * \brief Implementation of syntax tree node denoting variable in expression.
 *
 * \since 07.05.2016
 * \author agor
 */

#include "Variable.h"
#include "Visitor.h"


Variable::Variable() : Expression(EVariable) {
}


Variable::Variable(string name) : Expression(EVariable), name(name) {}

 void Variable::traverse(Visitor &visitor) const throw(TraverseException) {
	visitor.visit(shared_from_this());
}

 bool Variable::isComplete() const{
	return true;
}
 
//template <>
//bool expressionTypeOf<Variable>(shared_ptr<Expression> exprInstance){
//    return (exprInstance->type == EVariable);
//}