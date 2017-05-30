/**
 * @file Expression.cpp
 *
 * @brief Implementation of basic functions for abstract Expression.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "Expression.h"

Expression::Expression(string name) : name(name) {
}

Expression::~Expression() {
	// TODO Auto-generated destructor stub
}

string Expression::getName() const
{
	return this->name;
}

