/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file MultNumeratorDenominatorRuleTest.cpp
 * 
 * Tests for MultNumeratorDenominatorRule class .
 *
 * @since 10.01.2018
 * @author agor
 */

#include <gtest/gtest.h>

#include "MultNumeratorDenominatorRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Pow.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_MultNumeratorDenominatorRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_MultNumeratorDenominatorRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PMult> tests;
    std::vector<PExpression> expectedResults;
    
    // 3x*(4/x) = (3*(4*1))*(x^(1-1))
    tests.push_back(createMult(
            createMult(createConstant(3), createVariable("x")),
            createDiv(createConstant(4), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createMult(createConstant(4), createConstant(1))),
            createPow(createVariable("x"), createSub(createConstant(1), createConstant(1)))
    ));

    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultNumeratorDenominatorRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        string expected = to_string(expectedResults[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_MultNumeratorDenominatorRuleTest, DISABLE_visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PMult> tests;
    
    // x^2
    //tests.push_back(createPow(createVariable("x"), createConstant(2)));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultNumeratorDenominatorRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}