/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file PowConstantRuleTest.cpp
 * 
 * Tests for PowConstantRule class .
 *
 * @since 16.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "PowConstantRule.h"
#include <Constant.h>
#include <Pow.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_PowConstantRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_PowConstantRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PPow> tests;
    std::vector<PExpression> expectedResults;
    
    // 121^0.5 = 11
    tests.push_back(createPow(createConstant(121),createConstant(0.5)));
    expectedResults.push_back(createConstant(11));
    
    // x^0 = 1
    tests.push_back(createPow(createVariable("x"),createConstant(0)));
    expectedResults.push_back(createConstant(1));
    
    // x^1 = x
    tests.push_back(createPow(createVariable("x"),createConstant(1)));
    expectedResults.push_back(createVariable("x"));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        PowConstantRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        string expected = to_string(expectedResults[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_PowConstantRuleTest, visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PPow> tests;
    
    // x^y
    tests.push_back(createPow(createVariable("x"), createVariable("y")));
    
    // 5^x
    tests.push_back(createPow(createConstant(5), createVariable("x")));
    
    // (x^2)^0.5
    tests.push_back(createPow(createPow(createVariable("x"), createConstant(2)),createConstant(0.5)));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        PowConstantRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}