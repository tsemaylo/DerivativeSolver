/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumWithNullArgumentRuleTest.cpp
 * 
 * Tests for SumWithNullArgumentRule class .
 *
 * @since 29.09.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "SumWithNullArgumentRule.h"
#include <Constant.h>
#include <Sum.h>
#include <ExpressionFactory.h>

class FX_SumWithNullArgumentRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_SumWithNullArgumentRuleTest, visit_SumOfTwoConstants_NothingChangedFalse) {
    SumWithNullArgumentRule rule(createSum(createConstant(2.0), createConstant(3.0)));

    ASSERT_FALSE(rule.apply());
}

TEST_F(FX_SumWithNullArgumentRuleTest, visit_LeftArgumentIsZero_True) {
    SumWithNullArgumentRule rule(createSum(createConstant(0.0), createVariable("x")));

    ASSERT_TRUE(rule.apply());

    PExpression optExp = rule.getOptimizedExpression();

    ASSERT_TRUE(isTypeOf<Variable>(optExp));
    ASSERT_STREQ("x", SPointerCast<Variable>(optExp)->name.c_str());
}

TEST_F(FX_SumWithNullArgumentRuleTest, visit_RightArgumentIsZero_True) {
    SumWithNullArgumentRule rule(createSum(createVariable("x"), createConstant(0.0)));

    ASSERT_TRUE(rule.apply());

    PExpression optExp = rule.getOptimizedExpression();

    ASSERT_TRUE(isTypeOf<Variable>(optExp));
    ASSERT_STREQ("x", SPointerCast<Variable>(optExp)->name.c_str());
}
