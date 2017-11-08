/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumConstantsRuleTest.cpp
 * 
 * Tests for SumConstantsRule class .
 *
 * @since 11.09.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "SumConstantsRule.h"
#include <Constant.h>
#include <Sum.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_SumConstantsRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_SumConstantsRuleTest, visit_SumOfTwoConstants_Constant) {
    SumConstantsRule rule(createSum(createConstant(2.0), createConstant(3.0)));
    
    ASSERT_TRUE(rule.apply());
    
    PExpression optExp=rule.getOptimizedExpression();
    ASSERT_TRUE(isTypeOf<Constant>(optExp));
    
    PConstant optExpTyped = SPointerCast<Constant>(optExp);
    ASSERT_DOUBLE_EQ(5.0, optExpTyped->value);
}


TEST_F(FX_SumConstantsRuleTest, visit_OneArgumentIsNotConstants_False) {
    SumConstantsRule rule(createSum(createVariable("x"), createConstant(3.0)));
    
    ASSERT_FALSE(rule.apply());
    
    PExpression optExp=rule.getOptimizedExpression();
    // was it a sum? 
    ASSERT_TRUE(isTypeOf<Sum>(optExp));
    
    // assuming that the sum is a right one, dont perform any tests
}
