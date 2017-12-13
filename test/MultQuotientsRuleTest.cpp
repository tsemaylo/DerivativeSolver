/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file MultQuotientsRuleTest.cpp
 * 
 * Tests for MultQuotientsRule class .
 *
 * @since 13.12.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "MultQuotientsRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_MultQuotientsRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_MultQuotientsRuleTest, visit_OptimizableCases_ApplicableAndExpected) {    
    std::vector<PMult> tests;
    std::vector<PExpression> expectedResults;
    
    // 2*(3*x) = 6*x
    tests.push_back(createMult(createConstant(2), createMult(createConstant(3), createVariable("x"))));
    expectedResults.push_back(createMult(createConstant(6), createVariable("x")));

    // (3*x)*2 = 6*x
    tests.push_back(createMult(createMult(createConstant(3), createVariable("x")), createConstant(2)));
    expectedResults.push_back(createMult(createConstant(6), createVariable("x")));
    
    // (x*3)*2 = 6*x
    tests.push_back(createMult(createMult(createVariable("x"), createConstant(3)), createConstant(2)));
    expectedResults.push_back(createMult(createConstant(6), createVariable("x")));
    
    // 2*(3/x) = 6*(1/x)
    tests.push_back(createMult(createConstant(2), createDiv(createConstant(3), createVariable("x"))));
    expectedResults.push_back(createMult(createConstant(6), createDiv(createConstant(1), createVariable("x"))));
    
    // (3/x)*2 = 6*(1/x)
    tests.push_back(createMult(createDiv(createConstant(3), createVariable("x")), createConstant(2)));
    expectedResults.push_back(createMult(createConstant(6), createDiv(createConstant(1), createVariable("x"))));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultQuotientsRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        std::string expected = to_string(expectedResults[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_MultQuotientsRuleTest, visit_CantBeOptimized_NotApplicable) {
    std::vector<PMult> tests;
    
    // 2*x
    tests.push_back(createMult(createConstant(2), createVariable("x")));

    // (y*x)*2 
    tests.push_back(createMult(createMult(createVariable("x"), createVariable("x")), createConstant(2)));
    
    // 2*(x/3) = 6*(1/x)
    tests.push_back(createMult(createConstant(2), createDiv(createVariable("x"), createConstant(3))));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultQuotientsRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        std::string expected = to_string(tests[testId]);
        std::string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}