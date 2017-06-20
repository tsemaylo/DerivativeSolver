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
#include <memory>

#include "Parser.h"
#include "Expression.h"
#include "Constant.h"
#include "Variable.h"
#include "Function.h"

class ParserTest: public Parser {
public:

	// expose tokens for test purposes

	unique_ptr<list<Token>> getTokens(const string &strExpr) const {
		return Parser::getTokens(strExpr);
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
	unique_ptr<list<Token>> tknList = parser.getTokens("3*sin^2(x + a)/c");

	list<Token>::const_iterator tkn = tknList->begin();

	ASSERT_EQ(12, tknList->size());

	EXPECT_STREQ("3", tkn->getValue().c_str());
	EXPECT_EQ(TNumeric, tkn->getType());
	tkn++;
	
	EXPECT_STREQ("*", tkn->getValue().c_str());
	EXPECT_EQ(TOperation, tkn->getType());
	tkn++;

	ASSERT_STREQ("sin", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("^", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("2", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("(", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("x", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("+", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("a", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ(")", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("/", tkn->getValue().c_str());
	tkn++;
	ASSERT_STREQ("c", tkn->getValue().c_str());
	tkn++;
}

TEST_F(FX_Parser, isWhitespace_SpaceSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace(' '));
}

TEST_F(FX_Parser, isWhitespace_tabSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace('	'));
}

//TEST_F(FX_Parser, isWhitespace_AlphaSymbol_false) {
//	ParserTest parser;
//
//	// check the parsing tree for expresson a+2
//	list<Token> *tokensList=parser._getTokens();
//	tokensList->push_back(Token("a", TAlphaNumeric));
//	tokensList->push_back(Token("+", TOperation));
//	tokensList->push_back(Token("a", TNumeric));
//
//
//	Expression *expr=parser.parseTokens();
//	ASSERT_FALSE(NULL == expr);
//
//	Function *eRoot=(Function*) expr;
//	ASSERT_STREQ("+", eRoot->getName().c_str());
//
//	const Variable *varA=(const Variable *)eRoot->getArgument(0);
//	ASSERT_STREQ("a", varA->getName().c_str());
//
//	const Constant *const2=(const Constant *)eRoot->getArgument(1);
//	ASSERT_STREQ("2", const2->getName().c_str());
//}

