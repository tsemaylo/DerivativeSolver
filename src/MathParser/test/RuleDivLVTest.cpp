/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Test cases for RuleDivLV (left value division rule).
 *
 * @since 15.08.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <string>

#include "RuleDivLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Div.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleDivLV : public testing::Test {
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

TEST_F(FX_RuleDivLV, apply_LeftValueDivision_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createDiv());

    RuleDivLV ruleDivLV;
    EXPECT_TRUE(ruleDivLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PDiv div = SPointerCast<Div>(*i);
    EXPECT_TRUE(isTypeOf<Div>(div));

    PVariable divLArg = SPointerCast<Variable>(div->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(divLArg));
    EXPECT_STREQ("a", divLArg->name.c_str());
}

TEST_F(FX_RuleDivLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createDiv());
    stack.push_back(createVariable("a"));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Div>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleDivLV, apply_DivisionIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b/c)
    stack.push_back(createVariable("a"));
    stack.push_back(createDiv(createVariable("b"), createVariable("c")));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a/b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createDiv());
    stack.push_back(createVariable("b"));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
