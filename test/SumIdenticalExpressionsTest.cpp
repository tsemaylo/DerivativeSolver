/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumIdenticalExpressionsTest.cpp
 * 
 * Tests for SumIdenticalExpressions class .
 *
 * @since 06.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "SumIdenticalExpressions.h"
#include <Constant.h>
#include <Sum.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_SumIdenticalExpressionsTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_SumIdenticalExpressionsTest, visit_SumOfTwoConstants_Constant) {
    PSum testSum1 = createSum(createMult(createConstant("2"), createVariable("x")), createMult(createConstant("3"), createVariable("x")));
    
    SumIdenticalExpressions rule(testSum1);
    
    ASSERT_TRUE(rule.apply());
    
    PExpression optExp=rule.getOptimizedExpression();
    ASSERT_TRUE(isTypeOf<Mult>(optExp));
    
    PMult optExpTyped = SPointerCast<Mult>(optExp);
    
    PConstant quotient=SPointerCast<Constant>(optExpTyped->lArg);
    ASSERT_STREQ("5.00", quotient->value.c_str());
    
    PVariable var=SPointerCast<Variable>(optExpTyped->rArg);
    ASSERT_STREQ("x", var->name.c_str());
}

/*
TEST_F(FX_SumIdenticalExpressionsTest, visit_OneArgumentIsNotConstants_False) {
    SumConstantsRule rule(createSum(createVariable("x"), createConstant("3")));
    
    ASSERT_FALSE(rule.apply());
    
    PExpression optExp=rule.getOptimizedExpression();
    // was it a sum? 
    ASSERT_TRUE(isTypeOf<Sum>(optExp));
    
    // assuming that the sum is a right one, dont perform any tests
}

TEST_F(FX_SumIdenticalExpressionsTest, visit_ConstantIsNotANUmber_TraverseException) {
    SumConstantsRule rule(createSum(createConstant("x"), createConstant("3")));
    
    ASSERT_THROW(rule.apply(), TraverseException);
}
*/