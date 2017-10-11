/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file ComparatorTest.cpp
 *
 * test cases for comparator.
 * 
 * @since 09.10.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <string>

#include "Comparator.h"
#include "Variable.h"
#include "Sin.h"

#include "ExpressionFactory.h"

class FX_Comparator : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_Comparator, visit_SinXEqualSinY_NotEqual) {
    PExpression varX = createVariable("x");
    PExpression sinX = createSin(varX);
    PExpression varY = createVariable("y");
    PExpression sinY = createSin(varY);

    Comparator comparator(sinY);
    sinX->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_SinXEqualSinX_Equal) {
    PExpression varX1 = createVariable("x");
    PExpression sinX1 = createSin(varX1);
    PExpression varX2 = createVariable("x");
    PExpression sinX2 = createSin(varX2);

    Comparator comparator(sinX2);
    sinX1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_IdenticalSumExpression_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression sum1 = createSum(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression sum2 = createSum(varX_2, const3_2);

    Comparator comparator(sum2);
    sum1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_NotIdenticalSumExpressions_NotEqual) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression sum1 = createSum(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression varY = createVariable("y");
    PExpression sum2 = createSum(varX_2, varY);

    Comparator comparator(sum2);
    sum1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_SumAssociativeProperty_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression sum1 = createSum(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression sum2 = createSum(const3_2, varX_2);

    Comparator comparator(sum2);
    sum1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_IdenticalSubtractions_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression sub1 = createSub(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression sub2 = createSub(varX_2, const3_2);

    Comparator comparator(sub2);
    sub1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_SubtractionIsNotAssociative_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression sub1 = createSub(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression sub2 = createSub(const3_2, varX_2);

    Comparator comparator(sub2);
    sub1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_IdenticalMultExpression_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression mult1 = createMult(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression mult2 = createMult(varX_2, const3_2);

    Comparator comparator(mult2);
    mult1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_NotIdenticalMultExpressions_NotEqual) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression mult1 = createMult(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression varY = createVariable("y");
    PExpression mult2 = createMult(varX_2, varY);

    Comparator comparator(mult2);
    mult1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_MultAssociativeProperty_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression mult1 = createMult(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression mult2 = createMult(const3_2, varX_2);

    Comparator comparator(mult2);
    mult1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_IdenticalDivision_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression div1 = createDiv(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression div2 = createDiv(varX_2, const3_2);

    Comparator comparator(div2);
    div1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_DivisionIsNotAssociative_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression div1 = createDiv(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression div2 = createDiv(const3_2, varX_2);

    Comparator comparator(div2);
    div1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_IdenticalExponentation_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression Pow1 = createPow(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression pow2 = createPow(varX_2, const3_2);

    Comparator comparator(pow2);
    Pow1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_ExponentationIsNotAssociative_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression const3_1 = createConstant("3");
    PExpression pow1 = createPow(varX_1, const3_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression const3_2 = createConstant("3");
    PExpression pow2 = createPow(const3_2, varX_2);

    Comparator comparator(pow2);
    pow1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_ComparisonOfFunctions_Equal) {
    PExpression varX_1 = createVariable("x");
    PExpression exp_1 = createExp(varX_1);
    PExpression sin_1 = createSin(exp_1);
    PExpression cos_1 = createCos(sin_1);
    PExpression tan_1 = createTan(cos_1);
    PExpression ctan_1 = createCtan(tan_1);
    PExpression ln_1 = createLn(ctan_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression exp_2 = createExp(varX_2);
    PExpression sin_2 = createSin(exp_2);
    PExpression cos_2 = createCos(sin_2);
    PExpression tan_2 = createTan(cos_2);
    PExpression ctan_2 = createCtan(tan_2);
    PExpression ln_2 = createLn(ctan_2);

    Comparator comparator(ln_2);
    ln_1->traverse(comparator);
    ASSERT_TRUE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_ComparisonOfFunctions_NotEqual) {
    PExpression varX_1 = createVariable("x");
    PExpression exp_1 = createExp(varX_1);
    PExpression sin_1 = createSin(exp_1);
    PExpression cos_1 = createCos(sin_1);
    PExpression tan_1 = createTan(cos_1);
    PExpression ctan_1 = createCtan(tan_1);
    PExpression ln_1 = createLn(ctan_1);
    
    PExpression const3 = createConstant("3");
    PExpression exp_2 = createExp(const3);
    PExpression sin_2 = createSin(exp_2);
    PExpression cos_2 = createCos(sin_2);
    PExpression tan_2 = createTan(cos_2);
    PExpression ctan_2 = createCtan(tan_2);
    PExpression ln_2 = createLn(ctan_2);

    Comparator comparator(ln_2);
    ln_1->traverse(comparator);
    ASSERT_FALSE(comparator.areEqual());
}

TEST_F(FX_Comparator, visit_WhatIfRightExprIsNull_TraverseException) {
    PLn ln2=createLn(createVariable("x"));
    Comparator comparator2(createLn());
    EXPECT_THROW(ln2->traverse(comparator2), TraverseException);
}