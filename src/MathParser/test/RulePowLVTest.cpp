/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Test cases for RulePowLV (left value of exponentation rule).
 *
 * @since 16.08.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <string>

#include "RulePowLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Pow.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RulePowLV : public testing::Test {
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

TEST_F(FX_RulePowLV, apply_LeftValueOfExponentation_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createPow());

    RulePowLV rulePowLV;
    EXPECT_TRUE(rulePowLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PPow pow = SPointerCast<Pow>(*i);
    EXPECT_TRUE(isTypeOf<Pow>(pow));

    PVariable powLArg = SPointerCast<Variable>(pow->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(powLArg));
    EXPECT_STREQ("a", powLArg->name.c_str());
}

TEST_F(FX_RulePowLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createPow());
    stack.push_back(createVariable("a"));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Pow>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RulePowLV, apply_ExponentationOperationIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b^c)
    stack.push_back(createVariable("a"));
    stack.push_back(createPow(createVariable("b"), createVariable("c")));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a^b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createPow());
    stack.push_back(createVariable("b"));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
