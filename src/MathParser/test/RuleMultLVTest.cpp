/**
 * @file Test cases for RuleMultLV (left value division rule).
 *
 * @since 14.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleMultLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Mult.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleMultLV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
    
    Token lookAheadToken(string value, TokenType type) const {
        return Token(value, type);
    }
};

TEST_F(FX_RuleMultLV, apply_LeftValueMultiplication_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createMult());

    RuleMultLV ruleMultLV;
    EXPECT_TRUE(ruleMultLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PMult mult = SPointerCast<Mult>(*i);
    EXPECT_TRUE(isTypeOf<Mult>(mult));

    PVariable multLArg = SPointerCast<Variable>(mult->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(multLArg));
    EXPECT_STREQ("a", multLArg->name.c_str());
}

TEST_F(FX_RuleMultLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createMult());
    stack.push_back(createVariable("a"));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Mult>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleMultLV, apply_MultiplicationIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b*c)
    stack.push_back(createVariable("a"));
    stack.push_back(createMult(createVariable("b"), createVariable("c")));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleMultLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a*b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createMult());
    stack.push_back(createVariable("b"));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
