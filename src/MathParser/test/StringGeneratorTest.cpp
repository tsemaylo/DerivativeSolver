/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Tests for RuleSumLV (lft value summation rule).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <string>

#include "StringGenerator.h"
#include "Variable.h"
#include "Constant.h"
#include "Sum.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"

#include "ExpressionFactory.h"

class FX_StringGenerator : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_StringGenerator, visit_SimpleCase_ok) {
    // a+5*b-c/2 == ((a+(5*b))-(c/2))

    PExpression varB = createVariable("b");
    PExpression const5 = createConstant(5.0);
    PExpression mult = createMult(const5, varB);

    PExpression varA = createVariable("a");
    PExpression sum = createSum(varA, mult);

    PExpression varC = createVariable("c");
    PExpression const2 = createConstant(2.0);
    PExpression div = createDiv(varC, const2);

    PExpression sub = createSub(sum, div);

    StringGenerator strGen;
    sub->traverse(strGen);
    ASSERT_STREQ("(a+(5*b))-(c/2)", strGen.getLastVisitResult().c_str());
}

TEST_F(FX_StringGenerator, visit_SinusOfVariable_ok) {
    PExpression varA = createVariable("a");
    PExpression sin = createSin(varA);

    StringGenerator strGen;
    sin->traverse(strGen);
    ASSERT_STREQ("sin(a)", strGen.getLastVisitResult().c_str());
}

TEST_F(FX_StringGenerator, visit_SinusOfSum_ok) {
    PExpression varA = createVariable("a");
    PExpression varB = createVariable("b");
    PExpression sum = createSum(varA, varB);
    PExpression sin = createSin(sum);

    StringGenerator strGen;
    sin->traverse(strGen);
    ASSERT_STREQ("sin(a+b)", strGen.getLastVisitResult().c_str());
}