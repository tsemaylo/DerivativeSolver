/*
 * @file StringGenerator.cpp
 *
 * @brief Implementation of a Expression-String converter.
 *
 * @since 26.03.2016
 * @uthor agor
 */

#include "StringGenerator.h"

void StringGenerator::visit(const Constant& expr) throw(TraverseException) {
	this->result=expr.value;
}

void StringGenerator::visit(const Variable& expr) throw(TraverseException) {
	this->result=expr.name;
}

void StringGenerator::visit(const Sum& expr) throw(TraverseException) {
	expr.lArg->traverse(*this);
	string strLArg=this->getLastVisitResult();
	
	expr.rArg->traverse(*this);
	string strRArg=this->getLastVisitResult();
	
	this->setLastVisitResult(strLArg + "+" + strRArg);
}

void StringGenerator::visit(const Sub& expr) throw(TraverseException) {
	expr.lArg->traverse(*this);
	string strLArg=this->getLastVisitResult();
	
	expr.rArg->traverse(*this);
	string strRArg=this->getLastVisitResult();
	
	this->setLastVisitResult(strLArg + "-" + strRArg);
}

void StringGenerator::visit(const Mult& expr) throw(TraverseException) {
	expr.lArg->traverse(*this);
	string strLArg=this->getLastVisitResult();
	
	expr.rArg->traverse(*this);
	string strRArg=this->getLastVisitResult();
	
	this->setLastVisitResult(strLArg + "*" + strRArg);
}

void StringGenerator::visit(const Div& expr) throw(TraverseException) {
	expr.lArg->traverse(*this);
	string strLArg=this->getLastVisitResult();
	
	expr.rArg->traverse(*this);
	string strRArg=this->getLastVisitResult();
	
	this->setLastVisitResult(strLArg + "/" + strRArg);
}

string StringGenerator::getLastVisitResult() const {
	return this->result;
}

void StringGenerator::setLastVisitResult(string result) {
	this->result=result;
}

