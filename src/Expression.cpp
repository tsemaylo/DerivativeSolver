/**
 * @file Expression.cpp
 *
 * @brief Implementation of basic functions for abstract Expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Expression.h"

Expression::Expression(string name, ExpressionType type) : name(name), type(type){
}

string Expression::getName() const
{
	return this->name;
}

ExpressionType Expression::getType() const {
	return this->type;
}
