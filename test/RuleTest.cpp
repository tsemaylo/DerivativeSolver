/**
 * @file Test cases for Rule functions .
 *
 * @since 14.08.2016
 * @author agor
 */

#include <gtest/gtest.h>

#include "Rule.h"

class FX_Rule : public testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(FX_Rule, hasPriority_AdditionsVSOtherOperations_OtherOpersHavePriority) {
    EXPECT_TRUE(hasPriority(ESum, Token("*", TOperation)));
    EXPECT_TRUE(hasPriority(ESum, Token("/", TOperation)));
    EXPECT_TRUE(hasPriority(ESum, Token("\\", TOperation)));
    EXPECT_TRUE(hasPriority(ESum, Token("^", TOperation)));
    
    EXPECT_TRUE(hasPriority(ESub, Token("*", TOperation)));
    EXPECT_TRUE(hasPriority(ESub, Token("/", TOperation)));
    EXPECT_TRUE(hasPriority(ESub, Token("\\", TOperation)));
    EXPECT_TRUE(hasPriority(ESub, Token("^", TOperation)));
}

TEST_F(FX_Rule, hasPriority_MultiplicationsVSPower_PowerHasPriority) {
    EXPECT_TRUE(hasPriority(EMult, Token("^", TOperation)));
    EXPECT_TRUE(hasPriority(EDiv, Token("^", TOperation)));
}

TEST_F(FX_Rule, hasPriority_ArythmeticsVSFunctions_FunctionsHavePriority) {
    ExpressionType exprTypes[4] = {ESum, ESub, EMult, EDiv};
    for (int i = 0; i < 4; i++) {
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("sin", TAlphaNumeric)));
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("cos", TAlphaNumeric)));
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("tan", TAlphaNumeric)));
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("ctan", TAlphaNumeric)));
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("ln", TAlphaNumeric)));
        EXPECT_TRUE(hasPriority(exprTypes[i], Token("exp", TAlphaNumeric)));
    }
}

TEST_F(FX_Rule, hasPriority_AdditionsVSVarsAndConst_AdditionsHavePriority) {
    EXPECT_FALSE(hasPriority(ESum, Token("a", TAlphaNumeric)));
    EXPECT_FALSE(hasPriority(ESum, Token("1", TNumeric)));
    EXPECT_FALSE(hasPriority(ESub, Token("a", TAlphaNumeric)));
    EXPECT_FALSE(hasPriority(ESub, Token("1", TNumeric)));
}

TEST_F(FX_Rule, hasPriority_SameOperationOnBothSides_StillValid) {
    EXPECT_FALSE(hasPriority(ESum, Token("+", TOperation)));
    EXPECT_FALSE(hasPriority(ESum, Token("-", TOperation)));
    EXPECT_FALSE(hasPriority(ESub, Token("+", TOperation)));
    EXPECT_FALSE(hasPriority(ESub, Token("-", TOperation)));
    EXPECT_FALSE(hasPriority(EMult, Token("*", TOperation)));
    EXPECT_FALSE(hasPriority(EMult, Token("/", TOperation)));
    EXPECT_FALSE(hasPriority(EDiv, Token("*", TOperation)));
    EXPECT_FALSE(hasPriority(EDiv, Token("/", TOperation)));
}