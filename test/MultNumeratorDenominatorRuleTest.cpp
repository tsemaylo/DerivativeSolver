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
    
    // 3x*(4/x) = (3*4)*(x^0)
    tests.push_back(createMult(
            createMult(createConstant(3), createVariable("x")),
            createDiv(createConstant(4), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createConstant(4)),
            createPow(createVariable("x"), createConstant(0))
    ));
    
    // x*(4/x) = (1*4)*(x^0)
    tests.push_back(createMult(
            createVariable("x"),
            createDiv(createConstant(4), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(1), createConstant(4)),
            createPow(createVariable("x"), createConstant(0))
    ));
    
    // x3*(4/x) = (3*4)*(x^0)
    tests.push_back(createMult(
            createMult(createVariable("x"), createConstant(3)),
            createDiv(createConstant(4), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createConstant(4)),
            createPow(createVariable("x"), createConstant(0))
    ));
    
    // (4/x)*3x = (3*4)*(x^0)
    tests.push_back(createMult(
            createDiv(createConstant(4), createVariable("x")),
            createMult(createConstant(3), createVariable("x"))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createConstant(4)),
            createPow(createVariable("x"), createConstant(0))
    ));
    
    {
        // ((sin(x+cos(x))^4)*((1-sin(x))*cos(x+cos(x)))) * ((4/sin(x+cos(x))))
        // = (4 * ((1-sin(x))*cos(x+cos(x)))) * ((sin(x+cos(x))^3))
        auto _commonTerm = []() -> PExpression {
            // sin(x+cos(x))
            return createSin(createSum(createVariable("x"), createCos(createVariable("x"))));
        };
        auto _coefA = []() -> PExpression {
            // (1-sin(x))*cos(x+cos(x))
            return createMult(
                    createSub(createConstant(1), createSin(createVariable("x"))), 
                    createCos(createSum(createVariable("x"), createCos(createVariable("x"))))
            );
        };

        tests.push_back(createMult(
                createMult( createPow(_commonTerm(), createConstant(4)), _coefA() ),
                createDiv(createConstant(4), _commonTerm())
        ));
        expectedResults.push_back(createMult(
                createMult(createConstant(4), _coefA()),
                createPow(_commonTerm(), createConstant(3))
        ));
    }
    
    // 3x^3*(5/x^7) = (3*5)/(x^4)
    tests.push_back(createMult(
            createMult(createConstant(3), createPow(createVariable("x"), createConstant(3))),
            createDiv(createConstant(5), createPow(createVariable("x"), createConstant(7)))
    ));
    expectedResults.push_back(createDiv(
            createMult(createConstant(3), createConstant(5)),
            createPow(createVariable("x"), createConstant(4))
    ));
    
    // 3x^7*(5/x^3) = (3*5)*(x^4)
    tests.push_back(createMult(
            createMult(createConstant(3), createPow(createVariable("x"), createConstant(7))),
            createDiv(createConstant(5), createPow(createVariable("x"), createConstant(3)))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createConstant(5)),
            createPow(createVariable("x"), createConstant(4))
    ));
    
    // 3x^7*(5/x^y) = (3*5)*(x^(7-y))
    tests.push_back(createMult(
            createMult(createConstant(3), createPow(createVariable("x"), createConstant(7))),
            createDiv(createConstant(5), createPow(createVariable("x"), createVariable("y")))
    ));
    expectedResults.push_back(createMult(
            createMult(createConstant(3), createConstant(5)),
            createPow(createVariable("x"), createSub(createConstant(7), createVariable("y")))
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
    
    // x*3x
    tests.push_back(createMult(createVariable("x"), createMult(createConstant(3), createVariable("x"))));
    
    // (3/x)*(x/3)
    tests.push_back(createMult(
        createDiv(createConstant(3), createVariable("x")),
        createDiv(createVariable("x"), createConstant(3))
    ));
    
    // 2x*(x*5/x)
    tests.push_back(createMult(
        createMult(createConstant(2), createVariable("x")), 
        createMult(createVariable("x"), createDiv(createConstant(5), createVariable("x")))
    ));
    
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