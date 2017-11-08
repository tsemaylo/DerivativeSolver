/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file OptimizerTest.cpp
 * 
 * Tests for Optimizer.
 *
 * @since 09.09.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "Optimizer.h"
#include "Constant.h"
#include "Sum.h"

#include "ExpressionFactory.h"

class FX_Optimizer : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_Optimizer, visit_SumOfTwoConstants_Constant) {
    PSum exp = createSum(createConstant("2"), createConstant("3"));
    
    Optimizer optimizer;
    ASSERT_NO_THROW(exp->traverse(optimizer));
    
    PExpression optExp=optimizer.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(optExp));
    
    PConstant optExpTyped = SPointerCast<Constant>(optExp);
    
    ASSERT_DOUBLE_EQ(5.0, optExpTyped->value);
}

TEST_F(FX_Optimizer, visit_Subtraction_ApplicableAndSuccessfull) {
    std::vector<PSub> tests;
    std::vector<PExpression> expResults;
    
    tests.push_back(createSub(createMult(createConstant("5"), createVariable("x")), createMult(createConstant("3"), createVariable("x"))));
    expResults.push_back(createMult(createConstant("2"), createVariable("x")));
    
    tests.push_back(createSub(createMult(createConstant("3"), createVariable("x")), createMult(createConstant("5"), createVariable("x"))));
    expResults.push_back(createMult(createConstant("-2"), createVariable("x")));
    
    tests.push_back(createSub(createMult(createConstant("3"), createVariable("x")), createVariable("x")));
    expResults.push_back(createMult(createConstant("2"), createVariable("x")));
    
    tests.push_back(createSub(createVariable("x"), createMult(createConstant("3"), createVariable("x"))));
    expResults.push_back(createMult(createConstant("-2"), createVariable("x")));
    
    tests.push_back(createSub(createVariable("x"), createVariable("x")));
    expResults.push_back(createMult(createConstant("0"), createVariable("x")));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        Optimizer optimizer;
        EXPECT_NO_THROW(tests[testId]->traverse(optimizer)) << "Test ID=" << testId << " threw an exception!";
        PExpression actResult=optimizer.getLastVisitResult();
        string expected=to_string(expResults[testId]);
        string actual=to_string(actResult);
        EXPECT_TRUE(equals(expResults[testId], actResult)) << 
                "Result does not match for test ID=" << testId << "! (" 
                << expected << " != " << actual;
    }
}