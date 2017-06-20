/**
 * @file Parser.cpp
 *
 * @brief Implementation of the Parser.
 *
 * @since 25.03.2016
 * @Author: agor
 */

#include "Parser.h"

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

unique_ptr<list<Token>> Parser::getTokens(const string &strExpr) const {
	auto tokens=std::make_unique<list<Token>>();
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
			throw ParsingException();
		}

		if (tokenType != tokenTypeOfSymbol) {
			// new token

			// save old token
			if (!tokenValue.empty()) {
				Token token(tokenValue, tokenType);
				tokens->push_back(token);
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
		tokens->push_back(token);
	}
	
	return tokens;
}


bool Parser::doReduce(vector<unique_ptr<Expression>> &stack) const {
	// go through the list of rules and check if it is applicable to the provided stack
	list<unique_ptr<Rule>>::const_iterator rule = this->grammar.begin();
	list<unique_ptr<Rule>>::const_iterator lastRule = this->grammar.end();
	
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

void Parser::doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, vector<unique_ptr<Expression>> &stack) const {
	// opened question: can this function to be called recursively
	
	// LR parsing => shift-reduce method (bottom-up)
	// the method is chosen since it considers only forward scanning of tokens 
	// withoun backing up... it looks like easier to implement
	
	while(start!=end){
		// shift
		
		// fill up the stack with initial assumption regarding the non-terminal
		// @TODO extend 
		
		// UGLY UGLY UGLY
		if(start->getType() == TNumeric){
			stack.push_back(make_unique<Constant>(start->getValue()));
		}else if(start->getType() == TOperation){
			string op=start->getValue();
			if(op == "+"){
			}else if(op == "-"){
			}else if(op == "*"){
			}else if(op == "/"){
			}else{
				// @TODO throw unknown OP
			}
		}
		
		// reduce the stack untill no other posibility to reduce is available
		while(this->doReduce(stack)){
			// ???
		}
		
		start++; 
	}
	
	// at the end we should have only one element in the stack that means
	// everything is reduced and parsed
	if(stack.size()!=1){
		// if the stack is not completely reduced 
		// then probably grammar is not complete
		// or the syntax of the provided expression is incorrect

		throw ParsingException();
	}
}

unique_ptr<Expression> Parser::parseTokens(const unique_ptr<list<Token>> tokens) const {
	vector<unique_ptr<Expression>> stack;
	this->doParseTokens(tokens->begin(), tokens->end(), stack);
	return move(stack[0]); // @TODO what is happening here?
}

unique_ptr<Expression> Parser::parse(const string &strExpr) const throw(ParsingException) {
	return this->parseTokens(this->getTokens(strExpr));
}

