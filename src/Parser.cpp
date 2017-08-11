/**
 * @file Parser.cpp
 *
 * @brief Implementation of the Parser.
 *
 * @since 25.03.2016
 * @Author: agor
 */
#include <memory>

#include "bootstrap.h"
#include "Parser.h"
#include "Constant.h"
#include "Variable.h"
#include "Sum.h"
#include "Sub.h"
#include "Div.h"
#include "Mult.h"
#include "RuleSumLV.h"
#include "RuleSumRV.h"
#include "RuleSubLV.h"
#include "RuleSubRV.h"

Parser::Parser() {
	// initialize grammar
	
	/**
	 * some basic grammar to parse expressions with summation operation
     */
	
	// Rule #29
	this->grammar[0]=move(make_unique<RuleSumLV>());
	// Rule #30 #31
	this->grammar[1]=move(make_unique<RuleSumRV>());
	// Rule #32
	this->grammar[2]=move(make_unique<RuleSubLV>());
	// Rule #33 #34
	this->grammar[3]=move(make_unique<RuleSubRV>());
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
	return (c=='+' || c=='-' || c=='*' || c=='/'|| c=='\\' || c=='^');
}

bool Parser::isWhitespace(char c) const
{
	return (c==' ' || c=='\t');
}

list<Token> Parser::getTokens(const string &strExpr) const {
	list<Token> tokens;
			
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
			THROW(ParsingException, "Unknown character.", "'" + to_string(c) + "'");
		}

		if (tokenType != tokenTypeOfSymbol || tokenType == TGroupBracket) {
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
	
	return tokens;
}


bool Parser::doReduce(ParserStack &stack) const {
	// go through the list of rules and check if it is applicable to the provided stack
	for(auto &rule : this->grammar){
		// try to apply the rule to reduce the stack
		if(rule->apply(stack)){
			return true;
		}
	}
	
	return false;
}

shared_ptr<Expression> Parser::createOperation(const string opSymbol) const throw(ParsingException){
	if(opSymbol=="+"){
		return make_shared<Sum>();
	}
	if(opSymbol=="-"){
		return make_shared<Sub>();
	}
	if(opSymbol=="*"){
		return make_shared<Mult>();
	}
	if(opSymbol=="/" || opSymbol=="\\"){
		return make_shared<Div>();
	}
	
	THROW(ParsingException, "Unknown type of token (operation is not supported).", opSymbol);
}

shared_ptr<Expression> Parser::createExpression(const Token &token) const throw(ParsingException){
	
	switch(token.getType()){
		case TNumeric:
			return make_shared<Constant>(token.getValue());
		case TOperation:
			return createOperation(token.getValue());
		case TAlphaNumeric:
			// assuming that it is variable 
			return make_shared<Variable>(token.getValue());
		default:
			THROW(ParsingException, "Unknown type of token", "Token(" + token.getValue() + ")");
	}
}

list<Token>::const_iterator Parser::findEndOfParentheses(list<Token>::const_iterator start, list<Token>::const_iterator end) const throw(ParsingException){
	int openingBrackets=1; // we already have so far one oppening bracket
	int closingBrackets=0; // ...and it is not yet closed
	string trace="";
	
	while(start!=end){
		trace+=start->getValue();
		
		if(start->getType() != TGroupBracket){
			++start;
			continue;
		}
		
		if(start->getValue() == "("){
			openingBrackets++;
		}
		
		if(start->getValue() == ")"){
			closingBrackets++;
		}
		
		if(openingBrackets == closingBrackets){
			// fount it
			return start;
		}
			
		++start;
	}
	
	// ops, brackets are not closed
	THROW(ParsingException, "No closing bracket has been found.", trace);
}

void Parser::doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, ParserStack &stack) const throw(ParsingException){
	// opened question: can this function to be called recursively
	
	// LR parsing => shift-reduce method (bottom-up)
	// the method is chosen since it considers only forward scanning of tokens 
	// withoun backing up... it looks like easier to implement
	
	while(start!=end){
		// shift
		
		// fill up the stack with initial assumption regarding the non-terminal
		if(start->getType() == TGroupBracket){
			// is it an open bracket?
			
			// it must be an opening bracket
			if(start->getValue() == ")"){
				THROW(ParsingException, "Unexpected closing bracket ')'.", to_string(stack));
			}
			
			ParserStack subStack;
			++start; // this one is bracket - take the next one
			list<Token>::const_iterator endParentheses=findEndOfParentheses(start, end);
			this->doParseTokens(start, endParentheses, subStack);
			stack.push_back(subStack.front());
			start=endParentheses;
		}else{	
			stack.push_back(this->createExpression(*start));
		}
		
		// reduce the stack untill no other posibility to reduce is available
		while(this->doReduce(stack)){
			// ???
		}
		
		++start;
	}
	
	// at the end we should have only one element in the stack that means
	// everything is reduced and parsed
	if(stack.size()!=1){
		// if the stack is not completely reduced 
		// then probably grammar is not complete
		// or the syntax of the provided expression is incorrect

		THROW(ParsingException, "The specified expression is ambiguous. Not able to complitely reduce syntax tree.", to_string(stack));
	}
}

shared_ptr<Expression> Parser::parseTokens(const list<Token> &tokens) const {
	ParserStack stack;
	this->doParseTokens(tokens.begin(), tokens.end(), stack);
	return stack.front();
}

const shared_ptr<Expression> Parser::parse(const string &strExpr) const throw(ParsingException) {
	//list<Token> tokensList=;
	///@TODO tokensList.swap(this->getTokens(strExpr));
	return this->parseTokens(this->getTokens(strExpr));
}

