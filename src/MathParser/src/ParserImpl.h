/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Parser.h
 *
 * @brief Interface of the parser class.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef PARSERIMPL_H
#define PARSERIMPL_H

#include <memory>
#include <list>
#include <string>

#include "ParsingException.h"
#include "Expression.h"

class ParserStack;
class Token;
class Rule;

using namespace std;

/**
 * @brief Parser class implements parsing of the expression.
 *
 * Class is aimed to parse the given expression string into expression tree, which is intended to be analyzed later.
 */
class ParserImpl {
private:
    array<unique_ptr<Rule>, 17> grammar;

protected:
    /**
     * @brief Split the input string into tokens.
     * 
     * For instance: a+b*c => 'a', '+', 'b', '*', 'c'.
     * 
     * @param strExpr
     * 
     * @return The list of Tokens
     */
    list<Token> getTokens(const string &strExpr) const;

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
    PExpression parseTokens(const list<Token> &tokens) const;

    // @TODO very very private area... do something with it

    /**
     * Search for the closing bracket in the list of Tokens 
     * 
     * Method traverses the list of tokent starting from the first one after the opening bracket until it will find the closing bracket
     * 
     * @param [in]	start Iterator for starting token - next token after the opening bracket.
     * @param [in]	end Iterator for last available token in the list.
     * 
     * @return const_iterator pointing to the corresponding closing bracket.
     */
    list<Token>::const_iterator findEndOfParentheses(list<Token>::const_iterator start, list<Token>::const_iterator end) const throw (ParsingException);

    /**
     * Parse some part of the tokens.
     * 
     * @param [in]	start Iterator for starting token
     * @param [in]	end Iterator for last token.
     * @param [in/out]	Stack of parsed non-terminals.
     */
    void doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, ParserStack &stack) const throw (ParsingException);

    /**
     * Reduce the currant stack of non terminals.
     * 
     * @param [in/out]	Stack of parsed non-terminals.
     * 
     * @return true		If the stack was reduced.
     * @return false	If the stack was not reduced.
     */
    bool doReduce(ParserStack &stack, const Token &lookAheadToken) const;

    Token getLookAheadToken(list<Token>::const_iterator current, list<Token>::const_iterator end) const;

    PExpression createFunction(const string opSymbol) const throw (ParsingException);
            
    PExpression createOperation(const string opSymbol) const throw (ParsingException);

    /**
     * Scan the next token in the list of tokens and put the first assumtion about corresponding Expression to the stack.
     * 
     * @param [in] current Current (staerting) position in the list of tokens.
     * @param [in] end The end position in the list of tokent.
     * @param [out] stack The stack of parser to be extended,.
     * 
     * @return New iterator position in the list of tokens.
     */
    list<Token>::const_iterator shiftToStack(list<Token>::const_iterator current, list<Token>::const_iterator end, ParserStack &stack) const throw (ParsingException);

public:
    ParserImpl();

    const PExpression parse(const string &strExpr) const throw (ParsingException);
};

#endif /* PARSERIMPL_H */
