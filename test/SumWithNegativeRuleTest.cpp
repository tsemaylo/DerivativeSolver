/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumWithNegativeRuleTest.cpp
 * 
 * Tests for SumWithNegativeRule class .
 *
 * @since 11.02.2018
 * @author agor
 */

#include <gtest/gtest.h>

#include "SumWithNegativeRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Pow.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_SumWithNegativeRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_SumWithNegativeRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PSum> tests;
    std::vector<PExpression> expectedResults;
    
    // x+(-1*y) = x-y
    tests.push_back(createSum(
            createVariable("x"),
            createMult(createConstant(-1), createVariable("y"))
    ));
    expectedResults.push_back(createSub(
            createVariable("x"),
            createVariable("y")
    ));
    
    // (-1*y)+x = x-y
    tests.push_back(createSum(
            createMult(createConstant(-1), createVariable("y")),
            createVariable("x")    
    ));
    expectedResults.push_back(createSub(
            createVariable("x"),
            createVariable("y")
    ));
    
    // (-1*y)+(-1*x) = (-1*x)-y
    tests.push_back(createSum(
            createMult(createConstant(-1), createVariable("y")),
            createMult(createConstant(-1), createVariable("x"))    
    ));
    expectedResults.push_back(createSub(
            createMult(createConstant(-1), createVariable("x")),
            createVariable("y")
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        SumWithNegativeRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        string expected = to_string(expectedResults[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_SumWithNegativeRuleTest, visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PSum> tests;
    
    // x+x
    tests.push_back(createSum(createVariable("x"), createVariable("x")));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        SumWithNegativeRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}