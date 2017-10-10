/**
 * @file Expression.cpp
 *
 * @brief Implementation of basic functions for abstract Expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Expression.h"
#include "StringGenerator.h"
#include "Comparator.h"

Expression::Expression(ExpressionType type) : type(type){
}

string to_string(const PExpression expr){
    if(expr==nullptr){
        return "?";
    }
    StringGenerator stringGenerator;
    expr->traverse(stringGenerator);
    return stringGenerator.getLastVisitResult();
}

bool equals(const PExpression exprL, const PExpression exprR) throw (TraverseException){
    if(exprL == nullptr) {
        return false;
    }
    if(exprR == nullptr) {
        return false;
    }
    
    Comparator comparator(exprR);
    exprL->traverse(comparator);
    return comparator.areEqual();
}