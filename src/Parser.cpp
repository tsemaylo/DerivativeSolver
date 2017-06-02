/**
 * @file Parser.cpp
 *
 * @brief Implementation of the Parser.
 *
 * @since 25.03.2016
 * @Author: agor
 */

#include "Parser.h"

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


bool Parser::doReduce(vector<Expression *> *stack){
	// go through the list of rules and check if it is applicable to the provided stack
	list<Rule *>::const_iterator rule = rules.begin();
	list<Rule *>::const_iterator lastRule = rules.end();
	
	while(rule!=lastRule){
		// try to apply the rule to reduce the stack
		if((*rule)->apply(stack)){
			return true;
		}else{
			// rule is not applicable try next one
			rule++;
		}
	}
	
	return false;
}

Expression *Parser::doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, vector<Expression *> *stack){
	// opened question: can this function to be called recursively
	
	// LR parsing => shift-reduce method (bottom-up)
	// the method is chosen since it considers only forward scanning of tokens 
	// withoun backing up... it looks like easier to implement
	
	while(start!=end){
		// shift
		
		// fill up the stack with initial assumption regarding the non-terminal
		// @TODO extend 
		if(start->getType()==TNumeric){
			stack->push_back(new Constant(start->getValue()));
		}
		
		// reduce the stack untill no other posibility to reduce is available
		while(this->doReduce(stack)){
			// ???
		}
		
		start++; 
	}
	
	// at the end we should have only one element in the stack that means
	// everything is reduced and parsed
	if(stack->size()!=1){
		// if the stack is not completely reduced 
		// then probably grammar is not complete
		// or the syntax of the provided expression is incorrect
		
		// trow an exception
	}
	
	return stack->front();
}

Expression *Parser::parseTokens()
{
//	this->tokenTypes.clear();
//	this->tokenValues.clear();
//
//	Expression *expr=new Constant("42");
	
	vector<Expression *> stack;
	return this->doParseTokens(tokens.begin(), tokens.end(),&stack);
}

Expression *Parser::parse(const string &strExpr)
{
	this->getTokens(strExpr);
	return this->parseTokens();
}

