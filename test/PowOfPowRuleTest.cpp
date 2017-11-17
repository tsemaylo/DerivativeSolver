/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file PowOfPowRuleTest.cpp
 * 
 * Tests for PowOfPowRule class .
 *
 * @since 17.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "PowOfPowRule.h"
#include <Constant.h>
#include <Pow.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_PowOfPowRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_PowOfPowRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PPow> tests;
    std::vector<PExpression> expectedResults;
    
    // (x^2)^3 = x^(2*3)
    tests.push_back(createPow(createPow(createVariable("x"), createConstant(2)), createConstant(3)));
    expectedResults.push_back(createPow(createVariable("x"), createMult(createConstant(2),createConstant(3))));
    
    // (x^y)^3 = x^(y*3)
    tests.push_back(createPow(createPow(createVariable("x"), createVariable("y")), createConstant(3)));
    expectedResults.push_back(createPow(createVariable("x"), createMult(createVariable("y"), createConstant(3))));
    
    // (x^2)^y = x^(2*y)
    tests.push_back(createPow(createPow(createVariable("x"), createConstant(2)), createVariable("y")));
    expectedResults.push_back(createPow(createVariable("x"), createMult(createConstant(2), createVariable("y"))));
    
    // (1/x)^2 = x^(-1*2)
    tests.push_back(createPow(
        createDiv(createConstant(1), createVariable("x")), 
        createConstant(2)
    ));
    expectedResults.push_back(createPow(
        createVariable("x"), 
        createMult(createConstant(-1), createConstant(2))
    ));
    
    // (1/x^0.5)^2 = x^(-1*(0.5*2))
    tests.push_back(createPow(
        createDiv(createConstant(1), createPow(createVariable("x"), createConstant(0.5))), 
        createConstant(2)
    ));
    expectedResults.push_back(createPow(
        createVariable("x"), 
        createMult(createConstant(-1), createMult(createConstant(0.5), createConstant(2)))
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        PowOfPowRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        string expected = to_string(expectedResults[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_PowOfPowRuleTest, visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PPow> tests;
    
    // x^2
    tests.push_back(createPow(createVariable("x"), createConstant(2)));
    
    // (y/x)^2
    tests.push_back(createPow(
        createDiv(createVariable("y"), createVariable("x")),
        createConstant(2)
    ));
    
    // (5/x)^2
    tests.push_back(createPow(
        createDiv(createConstant(5), createVariable("x")),
        createConstant(2)
    ));
    
    // (1/(3*x))^2
    tests.push_back(createPow(
        createDiv(createConstant(1), createMult(createConstant(3),createVariable("x"))),
        createConstant(2)
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        PowOfPowRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}