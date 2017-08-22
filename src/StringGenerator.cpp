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

void StringGenerator::visit(const shared_ptr<const Constant> expr) throw (TraverseException) {
    this->setLastVisitResult(expr->value);
}

void StringGenerator::visit(const shared_ptr<const Variable> expr) throw (TraverseException) {
    this->setLastVisitResult(expr->name);
}

string StringGenerator::getArgString(const shared_ptr<const Expression> argExpr) throw (TraverseException) {
    if (argExpr == nullptr) {
        return "?";
    }

    argExpr->traverse(*this);
    return this->getLastVisitResult();
}

template <typename OpClass>
void StringGenerator::visitArythmeticalOp(const shared_ptr<const OpClass> expr, string op) throw (TraverseException) {
    string strLArg = this->getArgString(expr->lArg);
    string strRArg = this->getArgString(expr->rArg);
    this->setLastVisitResult("(" + strLArg + op + strRArg + ")");
}

template <typename OpClass>
void StringGenerator::visitFunction(const shared_ptr<const OpClass> expr, string fname) throw (TraverseException) {
    string strArg = this->getArgString(expr->arg);
    if (strArg.find('(', 0) != 0) {
        strArg = "(" + strArg + ")";
    }
    this->setLastVisitResult(fname + strArg);
}

void StringGenerator::visit(const shared_ptr<const Sum> expr) throw (TraverseException) {
    visitArythmeticalOp<Sum>(expr, "+");
}
void StringGenerator::visit(const shared_ptr<const Sub> expr) throw (TraverseException) {
    visitArythmeticalOp<Sub>(expr, "-");
}
void StringGenerator::visit(const shared_ptr<const Mult> expr) throw (TraverseException) {
    visitArythmeticalOp<Mult>(expr, "*");
}
void StringGenerator::visit(const shared_ptr<const Div> expr) throw (TraverseException) {
    visitArythmeticalOp<Div>(expr, "/");
}
void StringGenerator::visit(const shared_ptr<const Pow> expr) throw (TraverseException) {
    visitArythmeticalOp<Pow>(expr, "^");
}
void StringGenerator::visit(const shared_ptr<const Sin> expr) throw (TraverseException) {
    this->visitFunction<Sin>(expr, "sin");
}
void StringGenerator::visit(const shared_ptr<const Cos> expr) throw (TraverseException) {
    this->visitFunction<Cos>(expr, "cos");
}
void StringGenerator::visit(const shared_ptr<const Tan> expr) throw (TraverseException) {
    this->visitFunction<Tan>(expr, "tan");
}
void StringGenerator::visit(const shared_ptr<const Ctan> expr) throw (TraverseException) {
    this->visitFunction<Ctan>(expr, "ctan");
}
void StringGenerator::visit(const shared_ptr<const Ln> expr) throw (TraverseException) {
    this->visitFunction<Ln>(expr, "ln");
}
void StringGenerator::visit(const shared_ptr<const Exp> expr) throw (TraverseException) {
    this->visitFunction<Exp>(expr, "exp");
}

string StringGenerator::getLastVisitResult() const {
    return this->result;
}

void StringGenerator::setLastVisitResult(string result) {
    this->result = result;
}

