/*
 * @file StringGenerator.cpp
 *
 * @brief Implementation of a Expression-String converter.
 *
 * @since 26.03.2016
 * @uthor agor
 */

#include "StringGenerator.h"

StringGenerator::StringGenerator() {
	// TODO Auto-generated constructor stub

}

StringGenerator::~StringGenerator() {
	// TODO Auto-generated destructor stub
}

string StringGenerator::render(const Expression &expr) const
{
	return expr.getName();
}
