/**
 * @file Parser.cpp
 *
 * @brief Implementation of the Parser.
 *
 * @since 25.03.2016
 * @Author: agor
 */

#include "Parser.h"
#include "Constant.h"

Parser::Parser() {
}

Parser::~Parser() {
}

bool Parser::isAlpha(char c) const
{
	// assuming ASCII

	if(c >= 'a' && c <= 'z' ){
		return true;
	}

	if(c >= 'A' && c <= 'Z' ){
		return true;
	}

	return false;
}

bool Parser::isNumeric(char c) const
{
	// assuming ASCII

	if(c >= '0' && c <= '9' ){
		return true;
	}

	return false;
}

bool Parser::isGroupBracket(char c) const
{
	return (c=='(' || c==')');
}

bool Parser::isArithOperation(char c) const
{
	return (c=='+' || c=='-' || c=='*' || c=='/' || c=='^');
}

bool Parser::isWhitespace(char c) const
{
	return (c==' ' || c=='\t');
}

void Parser::getTokens(const string &strExpr)
{
	/**
	 * traverse the string and split it into valid tokens.
	 * The token is
	 * - sequence alphabet characters and numbers
	 * - groups brackets "(" ")"
	 * - math operations: +, -, *, /, ^
	 * - sequence of numbers
	 * This characters are ignored
	 * - whitespace characters
	 * Not allowed characters:
	 * - all other characters
	 */
	string tokenValue;
	TokenType tokenType=TNoToken;
	for(uint i=0;i<strExpr.length();i++){
		char c=strExpr[i];
		TokenType tokenTypeOfSymbol=TNoToken;
		if (this->isNumeric(c)) {
			tokenTypeOfSymbol=TNumeric;
		} else if (this->isAlpha(c)) {
			tokenTypeOfSymbol=TAlphaNumeric;
		} else if (this->isGroupBracket(c)) {
			tokenTypeOfSymbol=TGroupBracket;
		} else if (this->isArithOperation(c)) {
			tokenTypeOfSymbol=TOperation;
		} else if (this->isWhitespace(c)) {
			// ignore
			continue;
		}else{
			// @TODO: throw an exception - Not Allowed character
			continue;
		}

		if (tokenType != tokenTypeOfSymbol) {
			// new token

			// save old token
			if (!tokenValue.empty()) {
				Token token(tokenValue, tokenType);
				tokens.push_back(token);
			}
			// prepare a new token
			tokenValue.clear();
			tokenType = tokenTypeOfSymbol;
		}
		//  add symbol to token
		tokenValue += c;
	}

	// put the last token into list
	if (!tokenValue.empty()) {
		Token token(tokenValue, tokenType);
		tokens.push_back(token);
	}
}

/**
 * Parse some part of the tokens.
 * 
 * @param start Iterator for starting token
 * @param end Iterator for last token.
 * 
 * @return Expression as a fragmenzt of syntax tree.
 */
Expression *doParseTockens(list<Token>::const_iterator start, list<Token>::const_iterator end){

	// here we should build the syntax tree
	// what is sthe root node?
	// how do we parse the tokens? left to right?
	
	while(start!=end){
		// @TODO
		start++;
	}
	
	Expression *expr=new Constant("42");
	return expr;
}

Expression *Parser::parseTokens()
{
//	this->tokenTypes.clear();
//	this->tokenValues.clear();
//
//	Expression *expr=new Constant("42");
	
	return doParseTockens(tokens.begin(), tokens.end());
}

Expression *Parser::parse(const string &strExpr)
{
	this->getTokens(strExpr);
	return this->parseTokens();
}

