/**
 * @file Parser.cpp
 *
 * @brief Implementation of the Parser.
 *
 * @since 25.03.2016
 * @Author: agor
 */
#include <memory>

#include "Parser.h"

#include "Constant.h"
#include "Variable.h"
#include "Sum.h"
#include "Sub.h"
#include "Div.h"
#include "Mult.h"
#include "RuleSumLV.h"
#include "RuleSumRV.h"

Parser::Parser() {
	// initialize grammar
	
	/**
	 * some basic grammar to parse expressions with summation operation
     */
	
	// Expression Function(+) -> Function(L+)
	this->grammar[0]=move(make_unique<RuleSumLV>());
	// Function(L+) Expression -> Function(L+R)
	this->grammar[1]=move(make_unique<RuleSumRV>());
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
			throw ParsingException("Unknown token");
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
	
	throw ParsingException("Unknown type of token (operation is not supported).");
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
		case TGroupBracket:
			// Parenting bracket
			// @TODO so far no expression for this type
			// what about to introduce BracketedExpression? which should be eventually eliminated froom AST?
			// return make_unique<Function>(token.getValue());
			throw ParsingException("TGroupBracket is NYI");
		default:
			throw ParsingException("Unknown type of token");
	}
}

void Parser::doParseTokens(list<Token>::const_iterator start, list<Token>::const_iterator end, ParserStack &stack) const throw(ParsingException){
	// opened question: can this function to be called recursively
	
	// LR parsing => shift-reduce method (bottom-up)
	// the method is chosen since it considers only forward scanning of tokens 
	// withoun backing up... it looks like easier to implement
	
	while(start!=end){
		// shift
		
		// fill up the stack with initial assumption regarding the non-terminal
		stack.push_back(this->createExpression(*start));
				
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

		throw ParsingException("The specified expression is ambiguous. Not able to complitely reduce syntax tree.");
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

