/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file ExpressionTest.cpp
 * 
 * Test cases for Expression functions .
 *
 * @since 21.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "ExpressionFactory.h"

class FX_Expression : public testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(FX_Expression, toString_SinOfSum_OK) {
    PSin e=createSin(createSum(createVariable("x"), createConstant(3.0)));
    ASSERT_STREQ("sin(x+3)", to_string(e).c_str());
}

TEST_F(FX_Expression, equals_EqualityOfComplexExpression_OK) {
    PExpression varX_1 = createVariable("x");
    PExpression varY_1 = createVariable("y");
    PExpression pow_1 = createPow(varX_1, varY_1);
    PExpression exp_1 = createExp(pow_1);
    PExpression sin_1 = createSin(exp_1);
    PExpression cos_1 = createCos(sin_1);
    PExpression tan_1 = createTan(cos_1);
    PExpression ctan_1 = createCtan(tan_1);
    PExpression ln_1 = createLn(ctan_1);
    
    PExpression varX_2 = createVariable("x");
    PExpression varY_2 = createVariable("y");
    PExpression pow_2 = createPow(varX_2, varY_2);
    PExpression exp_2 = createExp(pow_2);
    PExpression sin_2 = createSin(exp_2);
    PExpression cos_2 = createCos(sin_2);
    PExpression tan_2 = createTan(cos_2);
    PExpression ctan_2 = createCtan(tan_2);
    PExpression ln_2 = createLn(ctan_2);
    
    ASSERT_TRUE(equals(ln_1, ln_2) == equals(ln_2, ln_1));
}
