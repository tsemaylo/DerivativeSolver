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

Expression::Expression(ExpressionType type) : type(type){
}

string to_string(const shared_ptr<Expression> &expr){
    if(expr==nullptr){
        return "?";
    }
    StringGenerator stringGenerator;
    expr->traverse(stringGenerator);
    return stringGenerator.getLastVisitResult();
}
