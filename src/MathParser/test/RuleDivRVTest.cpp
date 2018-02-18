/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleDivRVTest.cpp
 * 
 * Tests for RuleDivRV. Handling of right hand argument of division operation.
 *
 * @since 15.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleDivRV.h"
#include "Variable.h"
#include "Div.h"
#include "Sub.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleDivRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
};

TEST_F(FX_RuleDivRV, apply_NormalRightValueForDivision_Reducable) {
    ParserStack stack;
    stack.push_back(createDiv(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RuleDivRV ruleDivRV;
    EXPECT_TRUE(ruleDivRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PDiv div = SPointerCast<Div>(*i);
    EXPECT_TRUE(isTypeOf<Div>(div));

    PVariable divRArg = SPointerCast<Variable>(div->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(divRArg));
    EXPECT_STREQ("b", divRArg->name.c_str());
}

TEST_F(FX_RuleDivRV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("b"));
    stack.push_back(createDiv());
    
    RuleDivRV ruleDivRV;
    EXPECT_FALSE(ruleDivRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivRV, apply_RightSideArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // a/-b
    stack.push_back(createDiv(createVariable("a"), nullptr));
    stack.push_back(createSub(nullptr, createVariable("b")));

    RuleDivRV ruleDivRV;
    EXPECT_FALSE(ruleDivRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivRV, apply_DivisionWithoutLeftArgument_ParsingException) {
    ParserStack stack;

    // /a
    stack.push_back(createDiv());
    stack.push_back(createVariable("a"));
    
    RuleDivRV ruleDivRV;
    EXPECT_THROW(ruleDivRV.apply(stack, lookAheadToken()), ParsingException);
}