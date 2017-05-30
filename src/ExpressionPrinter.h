/**
 * @file ExressionPrinter.h
 *
 * @brief Interface for console printing tool.
 *
 * @since 26.03.2016
 * @author agor
 */

#ifndef SRC_EXPRESSIONPRINTER_H_
#define SRC_EXPRESSIONPRINTER_H_

#include <iostream>
#include <string>
#include "Expression.h"

using namespace std;

class ExpressionPrinter {
public:
	ExpressionPrinter();
	virtual ~ExpressionPrinter();

	void print(const Expression &expr) const;
};

#endif /* SRC_EXPRESSIONPRINTER_H_ */
