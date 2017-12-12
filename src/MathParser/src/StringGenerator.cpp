/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/*
 * @file StringGenerator.cpp
 *
 * @brief Implementation of a Expression-String converter.
 *
 * @since 26.03.2016
 * @uthor agor
 */

#include "StringGenerator.h"
#include <sstream>
#include <iomanip>
#include <ios>
#include "TraverseException.h"

using namespace std;

void StringGenerator::visit(const PConstConstant expr) throw (TraverseException) {
    std::stringstream strStream;
    strStream << std::defaultfloat << std::setprecision(2) << expr->value;  
    this->setLastVisitResult(strStream.str());
}

void StringGenerator::visit(const PConstVariable expr) throw (TraverseException) {
    this->setLastVisitResult(expr->name);
}

string StringGenerator::getArgString(const PConstExpression argExpr) throw (TraverseException) {
    if (argExpr == nullptr) {
        return "?";
    }

    argExpr->traverse(*this);
    return this->getLastVisitResult();
}

bool isBinaryOp(PExpression expr){
    if(expr == NULL){
        return false;
    }
        
    if(isTypeOf<Sum>(expr)){
        return true;
    }
    if(isTypeOf<Sub>(expr)){
        return true;
    }
    if(isTypeOf<Mult>(expr)){
        return true;
    }
    if(isTypeOf<Div>(expr)){
        return true;
    }
    if(isTypeOf<Pow>(expr)){
        return true;
    }
    return false;
}

template <typename PointerOpClass>
void StringGenerator::visitArythmeticalOp(const PointerOpClass expr, string op) throw (TraverseException) {
    string strLArg = this->getArgString(expr->lArg);
    string strRArg = this->getArgString(expr->rArg);
    if(isBinaryOp(expr->lArg)){
        strLArg = "(" + strLArg + ")";
    }
    if(isBinaryOp(expr->rArg)){
        strRArg = "(" + strRArg + ")";
    }
    this->setLastVisitResult(strLArg + op + strRArg);
}

template <typename PointerOpClass>
void StringGenerator::visitFunction(const PointerOpClass expr, string fname) throw (TraverseException) {
    string strArg = this->getArgString(expr->arg);
    if (strArg.find('(', 0) != 0) {
        strArg = "(" + strArg + ")";
    }
    this->setLastVisitResult(fname + strArg);
}

void StringGenerator::visit(const PConstSum expr) throw (TraverseException) {
    visitArythmeticalOp<PConstSum>(expr, "+");
}
void StringGenerator::visit(const PConstSub expr) throw (TraverseException) {
    visitArythmeticalOp<PConstSub>(expr, "-");
}
void StringGenerator::visit(const PConstMult expr) throw (TraverseException) {
    visitArythmeticalOp<PConstMult>(expr, "*");
}
void StringGenerator::visit(const PConstDiv expr) throw (TraverseException) {
    visitArythmeticalOp<PConstDiv>(expr, "/");
}
void StringGenerator::visit(const PConstPow expr) throw (TraverseException) {
    visitArythmeticalOp<PConstPow>(expr, "^");
}
void StringGenerator::visit(const PConstSin expr) throw (TraverseException) {
    this->visitFunction<PConstSin>(expr, "sin");
}
void StringGenerator::visit(const PConstCos expr) throw (TraverseException) {
    this->visitFunction<PConstCos>(expr, "cos");
}
void StringGenerator::visit(const PConstTan expr) throw (TraverseException) {
    this->visitFunction<PConstTan>(expr, "tan");
}
void StringGenerator::visit(const PConstCtan expr) throw (TraverseException) {
    this->visitFunction<PConstCtan>(expr, "ctan");
}
void StringGenerator::visit(const PConstLn expr) throw (TraverseException) {
    this->visitFunction<PConstLn>(expr, "ln");
}
void StringGenerator::visit(const PConstExp expr) throw (TraverseException) {
    this->visitFunction<PConstExp>(expr, "exp");
}

string StringGenerator::getLastVisitResult() const {
    return this->result;
}

void StringGenerator::setLastVisitResult(string result) {
    this->result = result;
}

