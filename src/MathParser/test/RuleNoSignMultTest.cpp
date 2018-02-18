/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleNoSignMultTest.cpp
 *
 * Test for RuleNoSignMult class.
 * 
 * @since 12.12.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleNoSignMult.h"
#include "Variable.h"
#include "Mult.h"
#include "Sub.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleNoSignMult : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
};

TEST_F(FX_RuleNoSignMult, apply_TwoCompletedExpressionInTheStack_Reducable) {
    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createVariable("b"));

    RuleNoSignMult ruleNoSignMult;
    EXPECT_TRUE(ruleNoSignMult.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    EXPECT_TRUE(isTypeOf<Mult>(*i));
    PMult mult = SPointerCast<Mult>(*i);
    
    EXPECT_TRUE(isTypeOf<Variable>(mult->lArg));
    EXPECT_EQ("a", SPointerCast<Variable>(mult->lArg)->name);
    EXPECT_TRUE(isTypeOf<Variable>(mult->rArg));
    EXPECT_EQ("b", SPointerCast<Variable>(mult->rArg)->name);
}

TEST_F(FX_RuleNoSignMult, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createSub(nullptr, createVariable("x")));
    stack.push_back(createMult(createVariable("x"), nullptr));
    
    RuleNoSignMult ruleNoSignMult;
    EXPECT_FALSE(ruleNoSignMult.apply(stack, lookAheadToken()));
}