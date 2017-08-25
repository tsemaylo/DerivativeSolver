/**
 * @file Tests for parser class.
 *
 * @since 24.04.2017
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
    EXPECT_TRUE(isTypeOf<Constant>(expr));
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
    EXPECT_TRUE(isTypeOf<Variable>(expr));
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
    EXPECT_TRUE(isTypeOf<Sum>(*exprIt));
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
    EXPECT_TRUE(isTypeOf<Sum>(*exprIt));
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

TEST_F(FX_Parser, shiftToStack_SinFunction_SinInStack) {
    list<Token> tokens;
    tokens.push_back(Token("sin", TAlphaNumeric));
    tokens.push_back(Token("Test", TNoToken));
            
    list<Token>::const_iterator start=tokens.begin();
    list<Token>::const_iterator end=tokens.end();
    
    ParserStack stack;
    
    ParserTest parser;
    start = parser.shiftToStack(start, end, stack);
    
    EXPECT_EQ("Test", start->value);
    
    ParserStack::const_iterator exprIt=stack.begin();
    shared_ptr<Expression> expr=*exprIt;
    EXPECT_TRUE(isTypeOf<Sin>(expr));
}

TEST_F(FX_Parser, parse_SimpleSummation_FunctionWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "a+b";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_TRUE(isTypeOf<Sum>(expr));
}

TEST_F(FX_Parser, parse_SummationWithParentness_SumWithTwoArgs) {
    ParserTest parser;
    const string strExpr = "(a+b)+c";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_TRUE(isTypeOf<Sum>(expr));

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
    ASSERT_TRUE(isTypeOf<Sum>(expr));

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
    ASSERT_TRUE(isTypeOf<Sum>(expr));

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
    ASSERT_TRUE(isTypeOf<Sub>(expr));

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
    ASSERT_TRUE(isTypeOf<Sum>(expr)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    
    // expecting Div: lArg=c    rArg=2
    ASSERT_NE(nullptr, sum->rArg);
    ASSERT_TRUE(isTypeOf<Div>(sum->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Div> divC2 = dynamic_pointer_cast<Div>(sum->rArg);
    
    shared_ptr<Variable> varC = dynamic_pointer_cast<Variable>(divC2->lArg);
    EXPECT_EQ("c", varC->name);
    shared_ptr<Constant> const2 = dynamic_pointer_cast<Constant>(divC2->rArg);
    EXPECT_EQ("2", const2->value);

    // expecting Mult: lArg=-1    rArg=(a*b)^n
    ASSERT_NE(nullptr, sum->lArg);
    ASSERT_TRUE(isTypeOf<Mult>(sum->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multL = dynamic_pointer_cast<Mult>(sum->lArg);
    
    shared_ptr<Constant> constN1 = dynamic_pointer_cast<Constant>(multL->lArg);
    EXPECT_EQ("-1", constN1->value);
    
    // expecting Pow: lArg=a*b      rArg=n
    ASSERT_NE(nullptr, multL->rArg);
    ASSERT_TRUE(isTypeOf<Pow>(multL->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Pow> powN = dynamic_pointer_cast<Pow>(multL->rArg);
    
    // expecting Mult. lArg=a     rArg=b
    ASSERT_NE(nullptr, powN->lArg);
    ASSERT_TRUE(isTypeOf<Mult>(powN->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multAB = dynamic_pointer_cast<Mult>(powN->lArg);
    shared_ptr<Variable> varA = dynamic_pointer_cast<Variable>(multAB->lArg);
    EXPECT_EQ("a", varA->name);
    shared_ptr<Variable> varB = dynamic_pointer_cast<Variable>(multAB->rArg);
    EXPECT_EQ("b", varB->name);
    
    // expecting Variable
    shared_ptr<Variable> varN = dynamic_pointer_cast<Variable>(powN->rArg);
    EXPECT_EQ("n", varN->name);
}

TEST_F(FX_Parser, parse_ExpressionWithFunctions_Function) {
    ParserTest parser;
    const string strExpr = "sin(x+2)";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    ASSERT_TRUE(isTypeOf<Sin>(expr));

    shared_ptr<Sin> sin = dynamic_pointer_cast<Sin>(expr);
    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(sin->arg);
    
    shared_ptr<Variable> varX = dynamic_pointer_cast<Variable>(sum->lArg);
    EXPECT_EQ("x", varX->name);
    shared_ptr<Constant> constTwo = dynamic_pointer_cast<Constant>(sum->rArg);
    EXPECT_EQ("2", constTwo->value);
}

TEST_F(FX_Parser, parse_ExpressionWithFunctions_ExpressionTree) {
    ParserTest parser;
    const string strExpr = "cos(x^2)*sin(x+2)-ln(tan(x/2))+exp(ctan(-x)+x)";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    
    StringGenerator stringGenerator;
    expr->traverse(stringGenerator);
    
    ASSERT_TRUE(isTypeOf<Sum>(expr)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(expr);
    
    // cos(x^2)*sin(x+2)-ln(tan(x/2))
    ASSERT_NE(nullptr, sum->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sub>(sum->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sub> subL = dynamic_pointer_cast<Sub>(sum->lArg);
    
    // cos(x^2)*sin(x+2)
    ASSERT_NE(nullptr, subL->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(subL->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multSinCos = dynamic_pointer_cast<Mult>(subL->lArg);
    
    // cos(x^2)
    ASSERT_NE(nullptr, multSinCos->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Cos>(multSinCos->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Cos> cos = dynamic_pointer_cast<Cos>(multSinCos->lArg);
    
    // x^2
    ASSERT_NE(nullptr, cos->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Pow>(cos->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Pow> powX2 = dynamic_pointer_cast<Pow>(cos->arg);
    ASSERT_NE(nullptr, powX2->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(powX2->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX_1 = dynamic_pointer_cast<Variable>(powX2->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(powX2->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> const2_1 = dynamic_pointer_cast<Constant>(powX2->rArg);
    ASSERT_STREQ("x", varX_1->name.c_str());
    ASSERT_STREQ("2", const2_1->value.c_str());
    
    // sin(x+2)
    ASSERT_NE(nullptr, multSinCos->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sin>(multSinCos->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sin> sin = dynamic_pointer_cast<Sin>(multSinCos->rArg);
    
    // x+2
    ASSERT_NE(nullptr, sin->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(sin->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sumX2 = dynamic_pointer_cast<Sum>(sin->arg);
    ASSERT_NE(nullptr, sumX2->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(sumX2->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX_2 = dynamic_pointer_cast<Variable>(sumX2->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(sumX2->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> const2_2 = dynamic_pointer_cast<Constant>(sumX2->rArg);
    ASSERT_STREQ("x", varX_2->name.c_str());
    ASSERT_STREQ("2", const2_2->value.c_str());
    
    // ln(tan(x/2))
    ASSERT_NE(nullptr, subL->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Ln>(subL->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Ln> lnTan = dynamic_pointer_cast<Ln>(subL->rArg);
    
    // tan(x/2)
    ASSERT_NE(nullptr, lnTan->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Tan>(lnTan->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Tan> tan = dynamic_pointer_cast<Tan>(lnTan->arg);
    
    // x/2
    ASSERT_NE(nullptr, tan->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Div>(tan->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Div> divX2 = dynamic_pointer_cast<Div>(tan->arg);
    ASSERT_NE(nullptr, divX2->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(divX2->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX_3 = dynamic_pointer_cast<Variable>(divX2->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(divX2->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> const2_3 = dynamic_pointer_cast<Constant>(divX2->rArg);
    ASSERT_STREQ("x", varX_3->name.c_str());
    ASSERT_STREQ("2", const2_3->value.c_str());
    
    // exp(ctan(-x)+x)
    ASSERT_NE(nullptr, sum->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Exp>(sum->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Exp> expR = dynamic_pointer_cast<Exp>(sum->rArg);
    
    // ctan(-x)+x
    ASSERT_NE(nullptr, expR->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(expR->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sumR = dynamic_pointer_cast<Sum>(expR->arg);
    
    // ctan(-x)
    ASSERT_NE(nullptr, sumR->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Ctan>(sumR->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Ctan> ctan = dynamic_pointer_cast<Ctan>(sumR->lArg);
    
    // -x
    ASSERT_NE(nullptr, ctan->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(ctan->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> multNeg = dynamic_pointer_cast<Mult>(ctan->arg);
    ASSERT_NE(nullptr, multNeg->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(multNeg->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> constNeg = dynamic_pointer_cast<Constant>(multNeg->lArg);
    ASSERT_STREQ("-1", constNeg->value.c_str());
    ASSERT_NE(nullptr, multNeg->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(multNeg->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX_4 = dynamic_pointer_cast<Variable>(multNeg->rArg);
    ASSERT_STREQ("x", varX_4->name.c_str());
    
    // x
    ASSERT_NE(nullptr, sumR->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(sumR->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX_5 = dynamic_pointer_cast<Variable>(sumR->rArg);
    ASSERT_STREQ("x", varX_5->name.c_str());
}

TEST_F(FX_Parser, parse_ExpressionWithFunctions2_ExpressionTree) {
    ParserTest parser;
    const string strExpr = "-cos(x)^(n+3)";

    shared_ptr<Expression> expr = parser.parse(strExpr);
    
    StringGenerator stringGenerator;
    expr->traverse(stringGenerator);
    
    ASSERT_TRUE(isTypeOf<Mult>(expr)) << stringGenerator.getLastVisitResult();
    shared_ptr<Mult> mult = dynamic_pointer_cast<Mult>(expr);
    
    ASSERT_NE(nullptr, mult->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(mult->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> constNeg = dynamic_pointer_cast<Constant>(mult->lArg);
    ASSERT_STREQ("-1", constNeg->value.c_str());
    
    // cos(x)^(n+3)
    ASSERT_NE(nullptr, mult->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Pow>(mult->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Pow> pow = dynamic_pointer_cast<Pow>(mult->rArg);
    
    // cos(x)
    ASSERT_NE(nullptr, pow->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Cos>(pow->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Cos> cos = dynamic_pointer_cast<Cos>(pow->lArg);
    ASSERT_NE(nullptr, cos->arg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(cos->arg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varX = dynamic_pointer_cast<Variable>(cos->arg);
    ASSERT_STREQ("x", varX->name.c_str());
    
    // (n+3)
    ASSERT_NE(nullptr, pow->rArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(pow->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(pow->rArg);
    ASSERT_NE(nullptr, sum->lArg) << stringGenerator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Variable>(sum->lArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Variable> varN = dynamic_pointer_cast<Variable>(sum->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(sum->rArg)) << stringGenerator.getLastVisitResult();
    shared_ptr<Constant> const2 = dynamic_pointer_cast<Constant>(sum->rArg);
    ASSERT_STREQ("n", varN->name.c_str());
    ASSERT_STREQ("3", const2->value.c_str());
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
