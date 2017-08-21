/**
 * @file Expression.cpp
 *
 * @brief Implementation of basic functions for abstract Expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Expression.h"

Expression::Expression(ExpressionType type) : type(type){
}

bool Expression::isFunctionType() const {
    return (
            (type == ESin) ||
            (type == ECos) ||
            (type == ETan) ||
            (type == ECtan) ||
            (type == ELn) ||
            (type == EExp)
    );
}
