/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file    Parser.h
 * 
 * Definition of the interface for the parser
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
 * Interface of mathematical exppression parser.
 */
class Parser {
public:
    /**
     * Parse the expression string.
     *
     * @param strExpr input string.
     * @return Root of the Expression tree.
     */
    virtual const PExpression parse(const std::string &strExpr) const throw (ParsingException) = 0;
};

#endif /* PARSER_H */

