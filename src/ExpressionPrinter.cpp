/**
 * @file ExressionPrinter.cpp
 *
 * @brief Implementation of an output representation printer for Expression.
 *
 * @since 26.03.2016
 * @author agor
 */

#include "ExpressionPrinter.h"
#include "StringGenerator.h"

ExpressionPrinter::ExpressionPrinter() {
	// TODO Auto-generated constructor stub

}

ExpressionPrinter::~ExpressionPrinter() {
	// TODO Auto-generated destructor stub
}

void ExpressionPrinter::print(const Expression &expr) const
{
	StringGenerator stringGenerator=StringGenerator();
	string strExpr=expr.printToString(stringGenerator);
	cout << strExpr << endl;
}
