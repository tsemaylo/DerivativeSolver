/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file LnOfExpRuleTest.cpp
 * 
 * Tests for LnOfExpRule class .
 *
 * @since 21.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "LnOfExpRule.h"
#include <Constant.h>
#include <Pow.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_LnOfExpRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_LnOfExpRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PLn> tests;
    std::vector<PExpression> expectedResults;
    
    // ln(exp(x)) = x
    tests.push_back(createLn(createExp(createVariable("x"))));
    expectedResults.push_back(createVariable("x"));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        LnOfExpRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        std::string expected = to_string(expectedResults[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_LnOfExpRuleTest, visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PLn> tests;
    
    // ln(x)
    tests.push_back(createLn(createVariable("x")));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        LnOfExpRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        std::string expected = to_string(tests[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}