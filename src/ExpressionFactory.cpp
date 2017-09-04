/**
 * @file ExpressionFactory.cpp
 * 
 * Implementation of factory functions for expression elements.
 * 
 * @author agor
 * @since 04.09.2017
 */

#include "ExpressionFactory.h"

PVariable createVariable(const string name) {
    return make_shared<Variable>(name);
}

PConstant createConstant(const string val) {
    return make_shared<Constant>(val);
}

PSum createSum() {
    return make_shared<Sum>();
}

PSum createSum(PExpression lArg, PExpression rArg) {
    PSum sum = createSum();
    sum->lArg = lArg;
    sum->rArg = rArg;
    return sum;
}

PSub createSub() {
    return make_shared<Sub>();
}

PSub createSub(PExpression lArg, PExpression rArg) {
    PSub sub = createSub();
    sub->lArg = lArg;
    sub->rArg = rArg;
    return sub;
}

PMult createMult() {
    return make_shared<Mult>();
}

PMult createMult(PExpression lArg, PExpression rArg) {
    PMult mult = createMult();
    mult->lArg = lArg;
    mult->rArg = rArg;
    return mult;
}

PDiv createDiv() {
    return make_shared<Div>();
}

PDiv createDiv(PExpression lArg, PExpression rArg) {
    PDiv div = createDiv();
    div->lArg = lArg;
    div->rArg = rArg;
    return div;
}

PPow createPow() {
    return make_shared<Pow>();
}

PPow createPow(PExpression lArg, PExpression rArg) {
    PPow pow = createPow();
    pow->lArg = lArg;
    pow->rArg = rArg;
    return pow;
}

PLn createLn(PExpression arg) {
    PLn ln = make_shared<Ln>();
    ln->arg = arg;
    return ln;
}

PExp createExp(PExpression arg) {
    PExp exp = make_shared<Exp>();
    exp->arg = arg;
    return exp;
}

PCos createCos(PExpression arg) {
    PCos cos = make_shared<Cos>();
    cos->arg = arg;
    return cos;
}

PSin createSin(PExpression arg) {
    PSin sin = make_shared<Sin>();
    sin->arg = arg;
    return sin;
}

PTan createTan(PExpression arg) {
    PTan tan = make_shared<Tan>();
    tan->arg = arg;
    return tan;
}

PCtan createCtan(PExpression arg) {
    PCtan ctan = make_shared<Ctan>();
    ctan->arg = arg;
    return ctan;
}