/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file MultIdenticalExpressionsRuleTest.cpp
 * 
 * Tests for MultIdenticalExpressionsRule class .
 *
 * @since 15.11.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "MultIdenticalExpressionsRule.h"
#include <Constant.h>
#include <Mult.h>
#include <Variable.h>
#include <ExpressionFactory.h>

class FX_MultIdenticalExpressionsRuleTest : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_MultIdenticalExpressionsRuleTest, visit_OptimizableExpressions_ApplicableAndExpected) {    
    std::vector<PMult> tests;
    std::vector<PExpression> expectedResults;
    
    // 5x^2*3x^3 = 15x^(2+3)
    tests.push_back(createMult(
        createMult(createConstant(5), createPow(createVariable("x"), createConstant(2))),
        createMult(createConstant(3), createPow(createVariable("x"), createConstant(3)))
    ));
    expectedResults.push_back(createMult(
            createConstant(15), 
            createPow(createVariable("x"), createSum(createConstant(2),createConstant(3)))
    ));
    
    // 5x*3x^3 = 15x^(1+3)
    tests.push_back(createMult(
        createMult(createConstant(5), createVariable("x")),
        createMult(createConstant(3), createPow(createVariable("x"), createConstant(3)))
    ));
    expectedResults.push_back(createMult(
            createConstant(15), 
            createPow(createVariable("x"), createSum(createConstant(1),createConstant(3)))
    ));
    
    // 5x^2*3x = 15x^(2+1)
    tests.push_back(createMult(
        createMult(createConstant(5), createPow(createVariable("x"), createConstant(2))),
        createMult(createConstant(3), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createConstant(15), 
            createPow(createVariable("x"), createSum(createConstant(2),createConstant(1)))
    ));
    
    // x*x = x^2
    tests.push_back(createMult(
        createVariable("x"),
        createVariable("x")
    ));
    expectedResults.push_back(createPow(createVariable("x"), createConstant(2)));
    
    
    // x * 5x = 5x^(1+1)
    tests.push_back(createMult(
        createVariable("x"),
        createMult(createConstant(5), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createConstant(5), 
            createPow(createVariable("x"), createSum(createConstant(1),createConstant(1)))
    ));
    
    // 5x * x = 5x^(1+1)
    tests.push_back(createMult(
        createMult(createConstant(5), createVariable("x")),
        createVariable("x")
    ));
    expectedResults.push_back(createMult(
            createConstant(5), 
            createPow(createVariable("x"), createSum(createConstant(1),createConstant(1)))
    ));
    
    // cos(x) * 5cos(x) = 5cos(x)^(1+1)
    tests.push_back(createMult(
        createCos(createVariable("x")),
        createMult(createConstant(5), createCos(createVariable("x")))
    ));
    expectedResults.push_back(createMult(
            createConstant(5), 
            createPow(createCos(createVariable("x")), createSum(createConstant(1),createConstant(1)))
    ));
    
    // cos(x) * cos(x)*5 = 5cos(x)^(1+1)
    tests.push_back(createMult(
        createCos(createVariable("x")),
        createMult(createCos(createVariable("x")), createConstant(5))
    ));
    expectedResults.push_back(createMult(
            createConstant(5), 
            createPow(createCos(createVariable("x")), createSum(createConstant(1),createConstant(1)))
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultIdenticalExpressionsRule rule(tests[testId]);
        EXPECT_TRUE(rule.apply()) << "Rule for test #" << testId << " was not applied!";
        string expected = to_string(expectedResults[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(expectedResults[testId], rule.getOptimizedExpression())) << 
                "Result doesn't match expectations: " << expected << 
                " != " << actual;
    }
}

TEST_F(FX_MultIdenticalExpressionsRuleTest, visit_NotOptimizableExpressions_NotApplicable) {    
    std::vector<PMult> tests;
    
    // 3*x
    tests.push_back(createMult(createConstant(5), createVariable("x")));
    
    // x*(x*cos(x))
    tests.push_back(createMult(
        createVariable("x"), 
        createMult(createVariable("x"), createCos(createVariable("x")))
    ));
    
    // x*(cos(x)*x)
    tests.push_back(createMult(
        createVariable("x"), 
        createMult(createCos(createVariable("x")), createVariable("x"))
    ));
    
    // (x*x)*cos(x))
    tests.push_back(createMult(
        createMult(createVariable("x"), createVariable("x")),
        createCos(createVariable("x"))
    ));
    
    // (x*cos(x))*x
    tests.push_back(createMult(
        createMult(createVariable("x"), createCos(createVariable("x"))),
        createVariable("x")
    ));
    
    // 5x^2*3y^3 
    tests.push_back(createMult(
        createMult(createConstant(5), createPow(createVariable("x"), createConstant(2))),
        createMult(createConstant(3), createPow(createVariable("y"), createConstant(3)))
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        MultIdenticalExpressionsRule rule(tests[testId]);
        EXPECT_FALSE(rule.apply()) << "Rule for test #" << testId << " was applied!";
        string expected = to_string(tests[testId]);
        string actual= to_string(rule.getOptimizedExpression());
        EXPECT_TRUE(equals(tests[testId], rule.getOptimizedExpression())) << 
                "Expression was corrupted: " << expected << 
                " != " << actual;
    }
}

//TEST_F(FX_MultIdenticalExpressionsRuleTest, visit_OneArgumentIsNotConstants_NotApplicable) {
//    MultConstantsRule rule(createMult(createVariable("x"), createConstant(3.0)));
//    ASSERT_FALSE(rule.apply());    
//    ASSERT_TRUE(isTypeOf<Mult>(rule.getOptimizedExpression()));
//}