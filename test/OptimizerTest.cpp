/**
 * @file Tests for Optimizer.
 *
 * @since 09.09.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "Optimizer.h"
#include "Constant.h"
#include "Sum.h"

#include "ExpressionFactory.h"

class FX_Differentiator : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_Differentiator, visit_SumOfTwoConstants_Constant) {
    PSum exp = createSum(createConstant("2"), createConstant("3"));
    
    Optimizer optimizer;
    ASSERT_NO_THROW(exp->traverse(optimizer));
    
    PExpression optExp=optimizer.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(optExp));
    
    PConstant optExpTyped = SPointerCast<Constant>(optExp);
    
    ASSERT_STREQ("5.00", optExpTyped->value.c_str());
}
