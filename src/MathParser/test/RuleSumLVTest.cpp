/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleSumLVTest.cpp
 * 
 * Tests for RuleSumLV (lft value summation rule).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleSumLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleSumLV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_RuleSumLV, apply_SimpleSummation_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createSum());

    RuleSumLV ruleSumLV;
    EXPECT_TRUE(ruleSumLV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();

    PSum sum = SPointerCast<Sum>(*i);
    EXPECT_TRUE(isTypeOf<Sum>(sum));

    PVariable sumLArg = SPointerCast<Variable>(sum->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(sumLArg));
    EXPECT_STREQ("a", sumLArg->name.c_str());
}

TEST_F(FX_RuleSumLV, apply_SimpleSummation_NotReducable) {
    ParserStack stack;

    stack.push_back(createSum());
    stack.push_back(createVariable("a"));

    RuleSumLV ruleSumLV;
    EXPECT_FALSE(ruleSumLV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Sum>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleSumLV, apply_SummationOperationWithoutArgument_NotReduced) {
    ParserStack stack;

    // ++a
    stack.push_back(createSum());
    stack.push_back(createSum());
    stack.push_back(createVariable("a"));

    RuleSumLV ruleSumLV;
    EXPECT_FALSE(ruleSumLV.apply(stack, Token("NA", TNoToken)));
}

TEST_F(FX_RuleSumLV, apply_LeftHandArgumentOfSummationIsAlreadyParsed_NotReduced) {
    ParserStack stack;

    // 3 a+? b
    stack.push_back(createConstant(3));
    stack.push_back(createSum(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RuleSumLV ruleSumLV;
    EXPECT_FALSE(ruleSumLV.apply(stack, Token("NA", TNoToken)));
}