/**
 * @file Tests for parser class.
 *
 * @since 24.04.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <string>
#include <list>
#include <vector>

#include "Parser.h"
#include "Expression.h"
#include "Constant.h"
#include "Variable.h"
#include "Function.h"

class ParserTest: public Parser {
public:

	// expose tokenValues for test purposes
	list<string> *_getTokenValues()
	{
		return &(this->tokenValues);
	}
	// expose tokenTypes for test purposes
	list<TokenType> *_getTokenTypes()
	{
		return &(this->tokenTypes);
	}

	void getTokens(const string &strExpr) {
		Parser::getTokens(strExpr);
	}

	bool isAlpha(char c) const {
		return Parser::isAlpha(c);
	}

	bool isNumeric(char c) const {
		return Parser::isNumeric(c);
	}

	bool isGroupBracket(char c) const {
		return Parser::isGroupBracket(c);
	}

	bool isArithOperation(char c) const {
		return Parser::isArithOperation(c);
	}

	bool isWhitespace(char c) const {
		return Parser::isWhitespace(c);
	}

	Expression *parseTokens() {
		return Parser::parseTokens();
	}
};

class FX_Parser: public testing::Test {
protected:
	virtual void SetUp() {
	}

	virtual void TearDown() {
	}
};

TEST_F(FX_Parser, getTokens_AllSymbolsExpression_ok) {
	ParserTest parser;
	parser.getTokens("3*sin^2(x + a)/c");

	list<string>::const_iterator tknVal = parser._getTokenValues()->begin();
	list<TokenType>::const_iterator tknTyp = parser._getTokenTypes()->begin();

	ASSERT_EQ(parser._getTokenValues()->size(), parser._getTokenTypes()->size());
	ASSERT_EQ(12, parser._getTokenValues()->size());

	EXPECT_STREQ("3", tknVal->c_str());
	EXPECT_EQ(TNumeric, *tknTyp);
	tknVal++;
	tknTyp++;

	EXPECT_STREQ("*", tknVal->c_str());
	EXPECT_EQ(TOperation, *tknTyp);
	tknVal++;
	tknTyp++;

	ASSERT_STREQ("sin", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("^", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("2", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("(", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("x", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("+", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("a", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ(")", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("/", tknVal->c_str());
	tknVal++;
	ASSERT_STREQ("c", tknVal->c_str());
	tknVal++;
}

TEST_F(FX_Parser, isWhitespace_SpaceSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace(' '));
}

TEST_F(FX_Parser, isWhitespace_tabSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace('	'));
}

TEST_F(FX_Parser, isWhitespace_AlphaSymbol_false) {
	ParserTest parser;

	// check the parsing tree for expresson a+2
	list<string> *tokensList=parser._getTokenValues();
	tokensList->push_back("a");
	tokensList->push_back("+");
	tokensList->push_back("2");


	Expression *expr=parser.parseTokens();
	ASSERT_FALSE(NULL == expr);

	Function *eRoot=(Function*) expr;
	ASSERT_STREQ("+", eRoot->getName().c_str());

	const Variable *varA=(const Variable *)eRoot->getArgument(0);
	ASSERT_STREQ("a", varA->getName().c_str());

	const Constant *const2=(const Constant *)eRoot->getArgument(1);
	ASSERT_STREQ("2", const2->getName().c_str());
}

