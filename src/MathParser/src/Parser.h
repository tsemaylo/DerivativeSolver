/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Parser.h
 * 
 * Definition of the interface for mathematical exppression parser.
 * 
 * @author  agor
 * @since 09.09.2017
 */

#ifndef PARSER_H
#define PARSER_H

#include <string>
#include "ParsingException.h"
#include "Expression.h"

/**
 * Parse the expression string.
 *
 * @param strExpr input string.
 * @return Root of the Expression tree.
 */
PExpression parse(const std::string &strExpr) throw (ParsingException);


#endif /* PARSER_H */

