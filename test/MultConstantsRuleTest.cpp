/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file MultConstantsRuleTest.cpp
 * 
 * Tests for MultConstantsRule class .
 *
 * @since 10.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "MultConstantsRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_MultConstantsRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_MultConstantsRuleTest, visit_MultOfWithConstants_ApplicableAndExpected) {    
    std::vector<PMult> tests;
    std::vector<PExpression> expectedResults;
    
    tests.push_back(createMult(createConstant(2.0), createConstant(3.5)));
    expectedResults.push_back(createConstant(7.0));
    
    tests.push_back(createMult(createConstant(0.0), createVariable("x")));
    expectedResults.push_back(createConstant(0.0));
    
    tests.push_back(createMult(createVariable("x"), createConstant(0.0)));
    expectedResults.push_back(createConstant(0.0));
    
    tests.push_back(createMult(createVariable("x"), createConstant(1.0)));
    expectedResults.push_back(createVariable("x"));
    
    tests.push_back(createMult(createConstant(1.0), createVariable("x")));
    expectedResults.push_back(createVariable("x"));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultConstantsRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression()));
    }
}

TEST_F(FX_MultConstantsRuleTest, visit_OneArgumentIsNotConstants_NotApplicable) {
    MultConstantsRule rule(createMult(createVariable("x"), createConstant(3.0)));
    ASSERT_FALSE(rule.apply());    
    ASSERT_TRUE(isTypeOf<Mult>(rule.getOptimizedExpression()));
}