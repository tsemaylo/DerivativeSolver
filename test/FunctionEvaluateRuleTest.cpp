/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file FunctionEvaluateRuleTest.cpp
 * 
 * Tests for FunctionEvaluateRule class .
 *
 * @since 21.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "FunctionEvaluateRule.tpp"
#include <Constant.h>
#include <Mult.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_FunctionEvaluateRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_FunctionEvaluateRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PSin> tests;
    std::vector<PExpression> expectedResults;
    
    tests.push_back(createSin(createConstant(0)));
    expectedResults.push_back(createConstant(0));
    
    double pi=3.14159265358979323846; 
    
    tests.push_back(createSin(createConstant(pi)));
    expectedResults.push_back(createConstant(0));
    
    tests.push_back(createSin(createConstant(pi/2.0)));
    expectedResults.push_back(createConstant(1));
    
    tests.push_back(createSin(createConstant(pi + pi/2.0)));
    expectedResults.push_back(createConstant(-1));
    
    tests.push_back(createSin(createConstant(2.0 * pi)));
    expectedResults.push_back(createConstant(0));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        FunctionEvaluateRule<Sin> rule(tests[testId], [](double x) -> double{ return std::sin(x); });
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        std::string expected = to_string(expectedResults[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_FunctionEvaluateRuleTest, visit_NotOptimizableExpressions_NotApplicable) {
    std::vector<PExpression> tests;

    // sin(0)
    tests.push_back(createSin(createConstant(0)));
    
    // cos(x)
    tests.push_back(createCos(createVariable("x")));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        FunctionEvaluateRule<Cos> rule(tests[testId], [](double x) -> double{ return std::cos(x); });
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        std::string expected = to_string(tests[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}