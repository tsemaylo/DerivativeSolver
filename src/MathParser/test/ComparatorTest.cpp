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