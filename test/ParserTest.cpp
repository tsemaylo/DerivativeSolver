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
#include "Sub.h"
#include "Mult.h"
#include "Div.h"
#include "Pow.h"
#include "StringGenerator.h"

class ParserTest : public Parser {
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

    list<Token>::const_iterator shiftToStack(list<Token>::const_iterator current, list<Token>::const_iterator end, ParserStack &stack) const throw (ParsingException) {
        return Parser::shiftToStack(current, end, stack);
    }

    list<Token>::const_iterator findEndOfParentheses(list<Token>::const_iterator start, list<Token>::const_iterator end) const throw (ParsingException) {
        return Parser::findEndOfParentheses(start, end);
    }
};

class FX_Parser : public testing::Test {
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

    EXPECT_STREQ("3", tkn->value.c_str());
    EXPECT_EQ(TNumeric, tkn->type);
    tkn++;

    EXPECT_STREQ("*", tkn->value.c_str());
    EXPECT_EQ(TOperation, tkn->type);
    tkn++;

    ASSERT_STREQ("sin", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("^", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("2", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("(", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("x", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("+", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("a", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ(")", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("/", tkn->value.c_str());
    tkn++;
    ASSERT_STREQ("c", tkn->value.c_str());
    tkn++;
}

TEST_F(FX_Parser, getTokens_MultipleParenting_ok) {
    ParserTest parser;
    list<Token> tknList = parser.getTokens("((()())())");

    ASSERT_EQ(10, tknList.size());

    for (auto tkn : tknList) {
        EXPECT_EQ(TGroupBracket, tkn.type);
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

TEST_F(FX_Parser, shiftToStack_NumericToken_ConstantExpressionInStack) {
    list<Token> tokens;
    tokens.push_back(Token("42", TNumeric));
    tokens.push_back(Token("Test", TNoToken));
            
    list<Token>::const_iterator start=tokens.begin();
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    start = parser.shiftToStack(start, end, stack);
    
    EXPECT_EQ("Test", start->value);
    
    ParserStack::const_iterator exprIt=stack.begin();
    shared_ptr<Expression> expr=*exprIt;
    EXPECT_EQ(EConstant, expr->type);
    EXPECT_STREQ("42", dynamic_pointer_cast<Constant>(expr)->value.c_str());
}

TEST_F(FX_Parser, shiftToStack_AlphaNummericToken_VariableExpressionInStack) {
    list<Token> tokens;
    tokens.push_back(Token("a", TAlphaNumeric));
    tokens.push_back(Token("Test", TNoToken));
            
    list<Token>::const_iterator start=tokens.begin();
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    start = parser.shiftToStack(start, end, stack);
    
    EXPECT_EQ("Test", start->value);
    
    ParserStack::const_iterator exprIt=stack.begin();
    shared_ptr<Expression> expr=*exprIt;
    EXPECT_EQ(EVariable, expr->type);
    EXPECT_STREQ("a", dynamic_pointer_cast<Variable>(expr)->name.c_str());
}

TEST_F(FX_Parser, shiftToStack_ArithmeticalOperationToken_SumExpressionInStack) {
    list<Token> tokens;
    tokens.push_back(Token("+", TOperation));
    tokens.push_back(Token("Test", TNoToken));
            
    list<Token>::const_iterator start=tokens.begin();
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    start = parser.shiftToStack(start, end, stack);
    
    EXPECT_EQ("Test", start->value);
    
    ParserStack::const_iterator exprIt=stack.begin();
    EXPECT_EQ(ESum, (*exprIt)->type);
}

TEST_F(FX_Parser, shiftToStack_BracketToken_ParsedSubExpressionInStack) {
    list<Token> tokens;
    tokens.push_back(Token("(", TGroupBracket));
    tokens.push_back(Token("a", TAlphaNumeric));
    tokens.push_back(Token("+", TOperation));
    tokens.push_back(Token("b", TAlphaNumeric));
    tokens.push_back(Token(")", TGroupBracket));
            
    list<Token>::const_iterator start=tokens.begin();
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    start = parser.shiftToStack(start, end, stack);
    
    EXPECT_EQ(end, start);
    
    ParserStack::const_iterator exprIt=stack.begin();
    EXPECT_EQ(ESum, (*exprIt)->type);
    EXPECT_TRUE((*exprIt)->isComplete());
}

TEST_F(FX_Parser, shiftToStack_OpenedBracketInTheEnd_ParsingException) {
    list<Token> tokens;
    tokens.push_back(Token("a", TAlphaNumeric));
    tokens.push_back(Token("+", TOperation));
    tokens.push_back(Token("(", TGroupBracket));
            
    list<Token>::const_iterator start=tokens.begin();
    ++start;
    ++start;
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    EXPECT_THROW(parser.shiftToStack(start, end, stack), ParsingException);
}

TEST_F(FX_Parser, parse_SimpleSummation_FunctionWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "a+b";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_EQ(expr->type, ESum);
}

TEST_F(FX_Parser, parse_SummationWithParentness_SumWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "(a+b)+c";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_EQ(expr->type, ESum);

    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(sum->rArg);
    EXPECT_EQ("c", varC->name);
    shared_ptr<Sum> sumL = dynamic_pointer_cast<Sum>(sum->lArg);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(sumL->lArg);
    EXPECT_EQ("a", varA->name);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(sumL->rArg);
    EXPECT_EQ("b", varB->name);
}

TEST_F(FX_Parser, parse_AdditionOperations_SumWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "a-b+c";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_EQ(expr->type, ESum);

    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(sum->rArg);
    EXPECT_EQ("c", varC->name);
    shared_ptr<Sub> subL = dynamic_pointer_cast<Sub>(sum->lArg);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(subL->lArg);
    EXPECT_EQ("a", varA->name);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(subL->rArg);
    EXPECT_EQ("b", varB->name);
}

TEST_F(FX_Parser, parse_AdditionOperationsWithParentness_SumWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "-(a-b)+c";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_EQ(expr->type, ESum);

    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(sum->rArg);
    EXPECT_EQ("c", varC->name);

    shared_ptr<Mult> multL = dynamic_pointer_cast<Mult>(sum->lArg);
    shared_ptr<Constant> constN1 = dynamic_pointer_cast<Constant>(multL->lArg);
    EXPECT_EQ("-1", constN1->value);
    shared_ptr<Sub> subL = dynamic_pointer_cast<Sub>(multL->rArg);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(subL->lArg);
    EXPECT_EQ("a", varA->name);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(subL->rArg);
    EXPECT_EQ("b", varB->name);
}

TEST_F(FX_Parser, parse_MixedExpression_SubWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "a-b*c";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_EQ(expr->type, ESub);

    shared_ptr<Sub> sub = dynamic_pointer_cast<Sub>(expr);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(sub->lArg);
    EXPECT_EQ("a", varA->name);
    
    shared_ptr<Mult> multR = dynamic_pointer_cast<Mult>(sub->rArg);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(multR->lArg);
    EXPECT_EQ("b", varB->name);
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(multR->rArg);
    EXPECT_EQ("c", varC->name);
}

TEST_F(FX_Parser, parse_MixedExpressionWithParentness_SumWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "-(a*b)^n+c/2";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    
    StringGenerator stringGenerator;
    expr->traverse(stringGenerator);
    
    // expecting Sum: lArg= -(a*b)^n     rArg=c/2
    ASSERT_EQ(ESum, expr->type) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    
    // expecting Div: lArg=c    rArg=2
    ASSERT_NE(nullptr, sum->rArg);
    ASSERT_EQ(EDiv, sum->rArg->type) << stringGenerator.getLastVisitResult();
    shared_ptr<Div> divC2 = dynamic_pointer_cast<Div>(sum->rArg);
    
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(divC2->lArg);
    EXPECT_EQ("c", varC->name);
    shared_ptr<Constant> const2 = dynamic_pointer_cast<Constant>(divC2->rArg);
    EXPECT_EQ("2", const2->value);

    // expecting Mult: lArg=-1    rArg=(a*b)^n
    ASSERT_NE(nullptr, sum->lArg);
    ASSERT_EQ(EMult, sum->lArg->type) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multL = dynamic_pointer_cast<Mult>(sum->lArg);
    
    shared_ptr<Constant> constN1 = dynamic_pointer_cast<Constant>(multL->lArg);
    EXPECT_EQ("-1", constN1->value);
    
    // expecting Pow: lArg=a*b      rArg=n
    ASSERT_NE(nullptr, multL->rArg);
    ASSERT_EQ(EPow, multL->rArg->type) << stringGenerator.getLastVisitResult();
    shared_ptr<Pow> powN = dynamic_pointer_cast<Pow>(multL->rArg);
    
    // expecting Mult. lArg=a     rArg=b
    ASSERT_NE(nullptr, powN->lArg);
    ASSERT_EQ(EMult, powN->lArg->type) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multAB = dynamic_pointer_cast<Mult>(powN->lArg);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(multAB->lArg);
    EXPECT_EQ("a", varA->name);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(multAB->rArg);
    EXPECT_EQ("b", varB->name);
    
    // expecting Variable
    shared_ptr<Variable> varN = dynamic_pointer_cast<Variable>(powN->rArg);
    EXPECT_EQ("n", varN->name);
}

TEST_F(FX_Parser, findEndOfParentheses_NormalCase_ok) {
    ParserTest parser;
    list<Token> tknList = parser.getTokens("a+(b+c)+(d+e)");
    list<Token>::const_iterator tkn = tknList.begin(); // 'a'
    ++tkn; // '+'
    ++tkn; // '('
    ++tkn; // 'b'
    list<Token>::const_iterator end = parser.findEndOfParentheses(tkn, tknList.end());
    EXPECT_STREQ(")", end->value.c_str());

    EXPECT_STREQ("b", tkn->value.c_str());

    tkn = end;
    ++tkn; // ')'
    ++tkn; // '+'
    ++tkn; // '('
    ++tkn; // 'd'

    end = parser.findEndOfParentheses(tkn, tknList.end());
    EXPECT_STREQ(")", end->value.c_str());
}

TEST_F(FX_Parser, findEndOfParentheses_MultipleParentness_ok) {
    ParserTest parser;
    list<Token> tknList = parser.getTokens("a+(b+(c+(d+e))+k)");
    list<Token>::const_iterator tkn = tknList.begin(); // 'a'
    ++tkn; // '+'
    ++tkn; // '('
    ++tkn; // 'b'
    list<Token>::const_iterator end = parser.findEndOfParentheses(tkn, tknList.end());
    EXPECT_STREQ(")", end->value.c_str());
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
