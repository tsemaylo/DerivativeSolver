/**
 * @file Test cases for Expression functions .
 *
 * @since 21.08.2016
 * @author agor
 */

#include <gtest/gtest.h>

#include "Sin.h"
#include "Variable.h"
#include "Constant.h"
#include "Sum.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"
#include "Pow.h"


class FX_Expression : public testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

//TEST_F(FX_Expression, DISABLED_isFunctionType_ElementaryFunctions_True) {
//    EXPECT_TRUE(Sin().isFunctionType());
//}
//
//TEST_F(FX_Expression, DISABLED_isFunctionType_OperationsVariablesAndConstants_False) {
//    EXPECT_FALSE(Variable("a").isFunctionType());
//    EXPECT_FALSE(Constant("42").isFunctionType());
//    EXPECT_FALSE(Sum().isFunctionType());
//    EXPECT_FALSE(Sub().isFunctionType());
//    EXPECT_FALSE(Mult().isFunctionType());
//    EXPECT_FALSE(Div().isFunctionType());
//    EXPECT_FALSE(Pow().isFunctionType());
//}