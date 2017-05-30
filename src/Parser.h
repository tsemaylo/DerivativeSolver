/**
 * @file Parser.h
 *
 * @brief Interface of the parser class.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_PARSER_H_
#define SRC_PARSER_H_

#include <list>
#include <string>
#include "Expression.h"
#include "Token.h"

using namespace std;

/**
 * @brief Parser class implements parsing of the expression.
 *
 * Class is aimed to parse the given expression string into expression tree, which is intended to be analyzed later.
 */
class Parser {

protected:
	list<Token> tokens;

	/**
	 * @brief Split the input string into tokens.
	 *
	 * For instance: a+b*c => 'a', '+', 'b', '*', 'c'.
	 *
	 * @return The list of string tokens.
	 */
	void getTokens(const string &strExpr);

	/**
	 * @brief Determine whether the symbol is an alphabetic character.
	 * @return True/False
	 */
	bool isAlpha(char c) const;

	/**
	 * @brief Determine whether the symbol is a number.
	 * @return True/False
	 */
	bool isNumeric(char c) const;

	/**
	 * @brief Determine whether the symbol is a grouping/functional brackets '(' ')'.
	 * @return True/False
	 */
	bool isGroupBracket(char c) const;

	/**
	 * @brief Determine whether the symbol is a arithmetic operation.
	 * @return True/False
	 */
	bool isArithOperation(char c) const;

	/**
	 * @brief Determine whether the symbol is a whitespace character.
	 * @return True/False
	 */
	bool isWhitespace(char c) const;

	/**
	 * @brief Analyze grammatically the list of tokens and build syntax tree.
	 * @param tokenList The list of tokens.
	 * @return Expression tree.
	 */
	Expression *parseTokens();
public:
	Parser();
	virtual ~Parser();

	/**
	 * Parse the expression string.
	 *
	 * @param strExpr input string.
	 * @return Root of the Expression tree.
	 */
	Expression *parse(const string &strExpr);
};

#endif /* SRC_PARSER_H_ */
