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

PLn createLn() {
    return make_shared<Ln>();
}

PLn createLn(PExpression arg) {
    PLn ln = createLn();
    ln->arg = arg;
    return ln;
}