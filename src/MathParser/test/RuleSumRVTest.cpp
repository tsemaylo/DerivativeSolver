/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Tests for RuleSumRV (process expression on the right sde of summation op).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleSumRV.h"
#include "Variable.h"
#include "Sum.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleSumRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_RuleSumRV, apply_SimpleSummation_Reducable) {

    ParserStack stack;
    PSum stackSum = SPointerCast<Sum>(createSum());
    stackSum->lArg = createVariable("b");
    stack.push_back(stackSum);
    stack.push_back(createVariable("a"));

    RuleSumRV ruleSumRV;
    EXPECT_TRUE(ruleSumRV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();

    PSum sum = SPointerCast<Sum>(*i);
    EXPECT_TRUE(isTypeOf<Sum>(sum));

    PVariable sumRArg = SPointerCast<Variable>(sum->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(sumRArg));
    EXPECT_STREQ("a", sumRArg->name.c_str());
}

TEST_F(FX_RuleSumRV, apply_SummationWithoutLeftArgument_Reducable) {

    ParserStack stack;
    stack.push_back(createSum());
    stack.push_back(createVariable("a"));

    RuleSumRV ruleSumRV;
    EXPECT_TRUE(ruleSumRV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();

    PVariable varA = SPointerCast<Variable>(*i);
    EXPECT_TRUE(isTypeOf<Variable>(varA));
    EXPECT_STREQ("a", varA->name.c_str());
}

TEST_F(FX_RuleSumRV, apply_SimpleSummation_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createSum());

    RuleSumRV ruleSumRV;
    EXPECT_FALSE(ruleSumRV.apply(stack, Token("NA", TNoToken)));

    EXPECT_EQ(2ul, stack.size());

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Variable>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Sum>(*i));
}

TEST_F(FX_RuleSumRV, apply_IncompleteExpressionOnTheRight_NotReduced) {
    ParserStack stack;
    // a++
    stack.push_back(createVariable("a"));
    stack.push_back(createSum());
    stack.push_back(createSum());

    RuleSumRV ruleSumRV;
    EXPECT_FALSE(ruleSumRV.apply(stack, Token("NA", TNoToken)));
}
