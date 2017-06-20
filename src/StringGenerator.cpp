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
	this->result=expr.getName();
}

void StringGenerator::visit(const Function& expr) throw(TraverseException) {
	// NYI
	this->result=string("NYI ") + expr.getName();
}

void StringGenerator::visit(const Variable& expr) throw(TraverseException) {
	this->result=expr.getName();
}

string StringGenerator::getLastVisitResult() const {
	return this->result;
}

void StringGenerator::setLastVisitResult(string result) {
	this->result=result;
}

