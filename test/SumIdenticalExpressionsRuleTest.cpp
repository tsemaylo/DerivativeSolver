/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file SumIdenticalExpressionsRuleTest.cpp
 * 
 * Tests for SumIdenticalExpressionsRule class .
 *
 * @since 06.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "SumIdenticalExpressionsRule.h"
#include <Constant.h>
#include <Sum.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_SumIdenticalExpressionsRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_SumIdenticalExpressionsRuleTest, visit_SimplifiableCases_RuleApplied) {
    std::vector<PSum> tests;
    std::vector<PExpression> expResults;
    
    tests.push_back(createSum(createMult(createConstant(2.0), createVariable("x")), createMult(createConstant(3.0), createVariable("x"))));
    expResults.push_back(createMult(createConstant(5.0), createVariable("x")));
    
    tests.push_back(createSum(createMult(createVariable("x"), createConstant(2.0)), createMult(createVariable("x"), createConstant(3.0))));
    expResults.push_back(createMult(createConstant(5.0), createVariable("x")));
    
    tests.push_back(createSum(createMult(createConstant(4.0), createVariable("x")), createVariable("x")));
    expResults.push_back(createMult(createConstant(5.0), createVariable("x")));
    
    tests.push_back(createSum(createVariable("x"), createVariable("x")));
    expResults.push_back(createMult(createConstant("2.00"), createVariable("x")));
    
    PCos cos2X=createCos(createMult(createVariable("x"),createConstant(2.0)));
    tests.push_back(createSum(cos2X, createMult(cos2X, createConstant(5.0))));
    expResults.push_back(createMult(createConstant(6.0), cos2X));
    
    for(unsigned int testId=0; testId<tests.size(); testId++){
        SumIdenticalExpressionsRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Test " << testId << "failed. Rule not applied.";
        string expected=to_string(expResults[testId]);
        string actual=to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expResults[testId], rule.getOptimizedExpression())) << 
                "Test " << testId << "failed. " << 
                "Reslt expression does not match expectations." << 
                expected << " != " << actual;
    }
}

TEST_F(FX_SumIdenticalExpressionsRuleTest, visit_NotPossibleToSum_RuleNotApplied) {
    std::vector<PSum> tests;
    
    tests.push_back(createSum(createVariable("x"), createVariable("y")));
    tests.push_back(createSum(createMult(createVariable("y"), createVariable("x")), createMult(createConstant(2.0), createVariable("x"))));
    tests.push_back(createSum(createMult(createConstant(2.0), createVariable("x")), createMult(createVariable("y"), createVariable("x"))));
    tests.push_back(createSum(createMult(createConstant(2.0), createVariable("x")), createMult(createConstant(2.0), createVariable("y"))));
    tests.push_back(createSum(createMult(createConstant(4.0), createVariable("x")), createPow(createVariable("x"), createConstant(2.0))));
    tests.push_back(createSum(createPow(createVariable("x"), createConstant(2.0)), createMult(createConstant(4.0), createVariable("x"))));
    
    for(unsigned int testId=0; testId<tests.size(); testId++){
        SumIdenticalExpressionsRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Test " << testId << "failed. Rule was applied.";
        string expected=to_string(tests[testId]);
        string actual=to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Test " << testId << "failed. " << 
                "Reslt expression does not match expectations." << 
                expected << " != " << actual;
    }
}