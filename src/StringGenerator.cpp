/*
 * @file StringGenerator.cpp
 *
 * @brief Implementation of a Expression-String converter.
 *
 * @since 26.03.2016
 * @uthor agor
 */

#include "StringGenerator.h"

#include <iostream>

void StringGenerator::visit(const shared_ptr<const Constant> expr) throw(TraverseException) {
	this->setLastVisitResult(expr->value);
}

void StringGenerator::visit(const shared_ptr<const Variable> expr) throw(TraverseException) {
	this->setLastVisitResult(expr->name);
}


string StringGenerator::getArgString(const shared_ptr<const Expression> argExpr) throw(TraverseException) {
	if(argExpr == nullptr){
		return "?";
	}
	
	argExpr->traverse(*this);
	return this->getLastVisitResult();
}

template <typename OpClass>
void StringGenerator::visitArythmeticalOp(const shared_ptr<const OpClass> expr, string op) throw(TraverseException) {
	string strLArg=this->getArgString(expr->lArg);
	string strRArg=this->getArgString(expr->rArg);
	this->setLastVisitResult(strLArg + op + strRArg);
}

void StringGenerator::visit(const shared_ptr<const Sum> expr) throw(TraverseException) {
	visitArythmeticalOp<Sum>(expr, "+");
}

void StringGenerator::visit(const shared_ptr<const Sub> expr) throw(TraverseException) {
	visitArythmeticalOp<Sub>(expr, "-");
}

void StringGenerator::visit(const shared_ptr<const Mult> expr) throw(TraverseException) {
	visitArythmeticalOp<Mult>(expr, "*");
}

void StringGenerator::visit(const shared_ptr<const Div> expr) throw(TraverseException) {
	visitArythmeticalOp<Div>(expr, "/");
}

string StringGenerator::getLastVisitResult() const {
	return this->result;
}

void StringGenerator::setLastVisitResult(string result) {
	this->result=result;
}

