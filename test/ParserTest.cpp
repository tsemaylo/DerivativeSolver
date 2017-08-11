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
#include "Sum.h"

class ParserTest: public Parser {
public:

	list<Token> getTokens(const string &strExpr) const {
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
	
	shared_ptr<Expression> createExpression(const Token &token) const throw(ParsingException){
		return Parser::createExpression(token);
	}
	
	list<Token>::const_iterator findEndOfParentheses(list<Token>::const_iterator start, list<Token>::const_iterator end) const throw(ParsingException){
		return Parser::findEndOfParentheses(start, end);
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
	list<Token> tknList = parser.getTokens("3*sin^2(x + a)/c");

	list<Token>::const_iterator tkn = tknList.begin();

	ASSERT_EQ(12, tknList.size());

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

TEST_F(FX_Parser, getTokens_MultipleParenting_ok) {
	ParserTest parser;
	list<Token> tknList = parser.getTokens("((()())())");

	ASSERT_EQ(10, tknList.size());

	for(auto tkn : tknList){
		EXPECT_EQ(TGroupBracket, tkn.getType());
	}
}

TEST_F(FX_Parser, isWhitespace_SpaceSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace(' '));
}

TEST_F(FX_Parser, isWhitespace_tabSymbol_true) {
	ParserTest parser;
	ASSERT_TRUE(parser.isWhitespace('	'));
}

TEST_F(FX_Parser, createExpression_NumericToken_ConstantExpression) {
	ParserTest parser;
	Token tkn("42", TNumeric);
	
	shared_ptr<Expression> expr = parser.createExpression(tkn);
	EXPECT_EQ(EConstant, expr->type);
	EXPECT_STREQ("42", ((Constant *)(expr.get()))->value.c_str());
}

TEST_F(FX_Parser, createExpression_AlphaNumericToken_VariableExpression) {
	ParserTest parser;
	Token tkn("X", TAlphaNumeric);
	
	shared_ptr<Expression> expr = parser.createExpression(tkn);
	EXPECT_EQ(EVariable, expr->type);
	EXPECT_STREQ("X", ((Variable *)(expr.get()))->name.c_str());
}

TEST_F(FX_Parser, createExpression_OperationToken_FunctionExpression) {
	ParserTest parser;
	Token tkn("+", TOperation);
	
	shared_ptr<Expression> expr = parser.createExpression(tkn);
	EXPECT_EQ(ESum, expr->type);
}

TEST_F(FX_Parser, parse_SimpleSummation_FunctionWithTwoArgs) {
	ParserTest parser;
	const string strExpr="a+b";
	
	shared_ptr<Expression> expr = parser.parse(strExpr);
	ASSERT_EQ(expr->type, ESum);
}

TEST_F(FX_Parser, parse_SummationWithParentness_SumWithTwoArgs) {
	ParserTest parser;
	const string strExpr="(a+b)+c";
	
	shared_ptr<Expression> expr = parser.parse(strExpr);
	EXPECT_EQ(expr->type, ESum);
	
	shared_ptr<Sum> sum=dynamic_pointer_cast<Sum>(expr);
	shared_ptr<Variable> varC=dynamic_pointer_cast<Variable>(sum->rArg);
	EXPECT_EQ("c", varC->name);
	shared_ptr<Sum> sumL=dynamic_pointer_cast<Sum>(sum->lArg);
	shared_ptr<Variable> varA=dynamic_pointer_cast<Variable>(sumL->lArg);
	EXPECT_EQ("a", varA->name);
	shared_ptr<Variable> varB=dynamic_pointer_cast<Variable>(sumL->rArg);
	EXPECT_EQ("b", varB->name);
}

TEST_F(FX_Parser, findEndOfParentheses_NormalCase_ok) {
	ParserTest parser;
	list<Token> tknList = parser.getTokens("a+(b+c)+(d+e)");
	list<Token>::const_iterator tkn = tknList.begin(); // 'a'
	++tkn; // '+'
	++tkn; // '('
	++tkn; // 'b'
	list<Token>::const_iterator end=parser.findEndOfParentheses(tkn, tknList.end());
	EXPECT_STREQ(")", end->getValue().c_str());
	
	EXPECT_STREQ("b", tkn->getValue().c_str());
	
	tkn=end;
	++tkn; // ')'
	++tkn; // '+'
	++tkn; // '('
	++tkn; // 'd'
	
	end=parser.findEndOfParentheses(tkn, tknList.end());
	EXPECT_STREQ(")", end->getValue().c_str());
}

TEST_F(FX_Parser, findEndOfParentheses_MultipleParentness_ok) {
	ParserTest parser;
	list<Token> tknList = parser.getTokens("a+(b+(c+(d+e))+k)");
	list<Token>::const_iterator tkn = tknList.begin(); // 'a'
	++tkn; // '+'
	++tkn; // '('
	++tkn; // 'b'
	list<Token>::const_iterator end=parser.findEndOfParentheses(tkn, tknList.end());
	EXPECT_STREQ(")", end->getValue().c_str());
}

TEST_F(FX_Parser, findEndOfParentheses_FailedParentness_ParsingException) {
	ParserTest parser;
	list<Token> tknList = parser.getTokens("a+(b+(c+(d+e)+k)");
	list<Token>::const_iterator tkn = tknList.begin(); // 'a'
	++tkn; // '+'
	++tkn; // '('
	++tkn; // 'b'
	ASSERT_THROW(parser.findEndOfParentheses(tkn, tknList.end()), ParsingException);
}
