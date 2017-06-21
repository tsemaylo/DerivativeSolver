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
#include <memory>
#include "Expression.h"
#include "Token.h"
#include "Rule.h"
#include "ParsingException.h"

using namespace std;

/**
 * @brief Parser class implements parsing of the expression.
 *
 * Class is aimed to parse the given expression string into expression tree, which is intended to be analyzed later.
 */
class Parser {

protected:
	list<unique_ptr<Rule>> grammar;

	/**
	 * @brief Split the input string into tokens.
	 *
	 * For instance: a+b*c => 'a', '+', 'b', '*', 'c'.
	 *
	 * @return The list of string tokens.
	 */
	unique_ptr<list<Token>> getTokens(const string &strExpr) const;

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
	unique_ptr<Expression> parseTokens(const unique_ptr<list<Token>> tokens) const;
	
	// @TODO very very private area... do something with it
	
	/**
	* Parse some part of the tokens.
	* 
	* @param [in]	start Iterator for starting token
	* @param [in]	end Iterator for last token.
	* @param [in/out]	Stack of parsed non-terminals.
	*/
	void doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, vector<unique_ptr<Expression>> &stack) const throw(ParsingException);
	
	/**
	 * Reduce the currant stack of non terminals.
	 * 
     * @param [in/out]	Stack of parsed non-terminals.
	 * 
     * @return true		If the stack was reduced.
	 * @return false	If the stack was not reduced.
     */
	bool doReduce(vector<unique_ptr<Expression>> &stack) const;
	
	unique_ptr<Expression> getInitialExpression(const Token &token) const throw(ParsingException);
	
public:

	/**
	 * Parse the expression string.
	 *
	 * @param strExpr input string.
	 * @return Root of the Expression tree.
	 */
	unique_ptr<Expression> parse(const string &strExpr) const throw(ParsingException);
};

#endif /* SRC_PARSER_H_ */
