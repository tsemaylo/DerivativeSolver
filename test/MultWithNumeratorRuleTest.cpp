/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file MultWithNumeratorRuleTest.cpp
 * 
 * Tests for MultWithNumeratorRule class .
 *
 * @since 11.02.2018
 * @author agor
 */

#include <gtest/gtest.h>

#include "MultWithNumeratorRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_MultWithNumeratorRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_MultWithNumeratorRuleTest, visit_MultOfWithConstants_ApplicableAndExpected) {    
    std::vector<PMult> tests;
    std::vector<PExpression> expectedResults;
    
    // 2*(3/x) = > (2*3)/x
    tests.push_back(createMult(
        createConstant(2.0), 
        createDiv(createConstant(3), createVariable("x"))
    ));
    expectedResults.push_back(createDiv(
        createMult(createConstant(2.0), createConstant(3.0)),
        createVariable("x")
    ));
    
    // (3/x)*2 = > (2*3)/x
    tests.push_back(createMult(
        createDiv(createConstant(3), createVariable("x")),
        createConstant(2.0)
    ));
    expectedResults.push_back(createDiv(
        createMult(createConstant(2.0), createConstant(3.0)),
        createVariable("x")
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultWithNumeratorRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression()));
    }
}

TEST_F(FX_MultWithNumeratorRuleTest, visit_OneArgumentIsNotConstants_NotApplicable) {
    std::vector<PMult> tests;
    
    tests.push_back(createMult(createVariable("x"), createConstant(3.0)));
    tests.push_back(createMult(
        createDiv(createConstant(3), createVariable("x")),
        createDiv(createVariable("x"), createConstant(3))
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultWithNumeratorRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}