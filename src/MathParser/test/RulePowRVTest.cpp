/**
 * @file Tests for RulePowRV. Handling of right hand argument of exponentation operation.
 *
 * @since 16.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RulePowRV.h"
#include "Variable.h"
#include "Pow.h"
#include "Sub.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RulePowRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
};

TEST_F(FX_RulePowRV, apply_NormalRightValueForExponentationOperation_Reducable) {
    ParserStack stack;
    stack.push_back(createPow(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RulePowRV rulePowRV;
    EXPECT_TRUE(rulePowRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PPow pow = SPointerCast<Pow>(*i);
    EXPECT_TRUE(isTypeOf<Pow>(pow));

    PVariable powRArg = SPointerCast<Variable>(pow->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(powRArg));
    EXPECT_STREQ("b", powRArg->name.c_str());
}

TEST_F(FX_RulePowRV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("b"));
    stack.push_back(createPow());
    
    RulePowRV rulePowRV;
    EXPECT_FALSE(rulePowRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowRV, apply_RightSideArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // a^-b
    stack.push_back(createPow(createVariable("a"), nullptr));
    stack.push_back(createSub(nullptr, createVariable("b")));

    RulePowRV rulePowRV;
    EXPECT_FALSE(rulePowRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowRV, apply_ExponentationOperationWithoutLeftArgument_ParsingException) {
    ParserStack stack;

    // ^a
    stack.push_back(createPow());
    stack.push_back(createVariable("a"));
    
    RulePowRV rulePowRV;
    EXPECT_THROW(rulePowRV.apply(stack, lookAheadToken()), ParsingException);
}