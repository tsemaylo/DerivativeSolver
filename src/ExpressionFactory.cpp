/**
 * @file ExpressionFactory.cpp
 * 
 * Implementation of factory functions for expression elements.
 * 
 * @author agor
 * @since 04.09.2017
 */

#include "ExpressionFactory.h"
#include "Pointers.h"

PVariable createVariable(const string name) {
    return MakeSPointer<Variable>(name);
}

PConstant createConstant(const string val) {
    return MakeSPointer<Constant>(val);
}

PSum createSum() {
    return MakeSPointer<Sum>();
}

PSum createSum(PExpression lArg, PExpression rArg) {
    PSum sum = createSum();
    sum->lArg = lArg;
    sum->rArg = rArg;
    return sum;
}

PSub createSub() {
    return MakeSPointer<Sub>();
}

PSub createSub(PExpression lArg, PExpression rArg) {
    PSub sub = createSub();
    sub->lArg = lArg;
    sub->rArg = rArg;
    return sub;
}

PMult createMult() {
    return MakeSPointer<Mult>();
}

PMult createMult(PExpression lArg, PExpression rArg) {
    PMult mult = createMult();
    mult->lArg = lArg;
    mult->rArg = rArg;
    return mult;
}

PDiv createDiv() {
    return MakeSPointer<Div>();
}

PDiv createDiv(PExpression lArg, PExpression rArg) {
    PDiv div = createDiv();
    div->lArg = lArg;
    div->rArg = rArg;
    return div;
}

PPow createPow() {
    return MakeSPointer<Pow>();
}

PPow createPow(PExpression lArg, PExpression rArg) {
    PPow pow = createPow();
    pow->lArg = lArg;
    pow->rArg = rArg;
    return pow;
}

PLn createLn() {
    return MakeSPointer<Ln>();
}

PLn createLn(PExpression arg) {
    PLn ln = createLn();
    ln->arg = arg;
    return ln;
}

PExp createExp() {
    return MakeSPointer<Exp>();
}

PExp createExp(PExpression arg) {
    PExp exp = createExp();
    exp->arg = arg;
    return exp;
}

PCos createCos() {
    return MakeSPointer<Cos>();
}

PCos createCos(PExpression arg) {
    PCos cos = createCos();
    cos->arg = arg;
    return cos;
}

PSin createSin() {
    return MakeSPointer<Sin>();
}

PSin createSin(PExpression arg) {
    PSin sin = createSin();
    sin->arg = arg;
    return sin;
}

PTan createTan() {
    return MakeSPointer<Tan>();
}

PTan createTan(PExpression arg) {
    PTan tan = createTan();
    tan->arg = arg;
    return tan;
}

PCtan createCtan() {
    return MakeSPointer<Ctan>();
}

PCtan createCtan(PExpression arg) {
    PCtan ctan = createCtan();
    ctan->arg = arg;
    return ctan;
}