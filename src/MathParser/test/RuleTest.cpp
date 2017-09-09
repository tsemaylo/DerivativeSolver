/**
 * @file Test cases for Rule functions .
 *
 * @since 14.08.2016
 * @author agor
 */

#include <gtest/gtest.h>

#include "Rule.h"

#include "Sum.h"
#include "Sub.h"
#include "Div.h"
#include "Mult.h"
#include "Pow.h"
#include "Sin.h"
#include "Token.h"

class FX_Rule : public testing::Test {
protected:
    virtual void SetUp() {
    }
    virtual void TearDown() {
    }
};

TEST_F(FX_Rule, hasPriority_AdditionsVSOtherOperations_OtherOpersHavePriority) {
    EXPECT_TRUE(hasPriority<Sum>(Token("*", TOperation)));
    EXPECT_TRUE(hasPriority<Sum>(Token("/", TOperation)));
    EXPECT_TRUE(hasPriority<Sum>(Token("\\", TOperation)));
    EXPECT_TRUE(hasPriority<Sum>(Token("^", TOperation)));
    
    EXPECT_TRUE(hasPriority<Sub>(Token("*", TOperation)));
    EXPECT_TRUE(hasPriority<Sub>(Token("/", TOperation)));
    EXPECT_TRUE(hasPriority<Sub>(Token("\\", TOperation)));
    EXPECT_TRUE(hasPriority<Sub>(Token("^", TOperation)));
}

TEST_F(FX_Rule, hasPriority_MultiplicationsVSPower_PowerHasPriority) {
    EXPECT_TRUE(hasPriority<Mult>(Token("^", TOperation)));
    EXPECT_TRUE(hasPriority<Div>(Token("^", TOperation)));
}

TEST_F(FX_Rule, hasPriority_ArythmeticsVSFunctions_FunctionsHavePriority) {
    EXPECT_TRUE(hasPriority<Sum>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sum>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sum>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sum>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sum>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sum>(Token("exp", TAlphaNumeric)));
    
    EXPECT_TRUE(hasPriority<Sub>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("exp", TAlphaNumeric)));

    EXPECT_TRUE(hasPriority<Sub>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Sub>(Token("exp", TAlphaNumeric)));
    
    EXPECT_TRUE(hasPriority<Div>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Div>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Div>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Div>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Div>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Div>(Token("exp", TAlphaNumeric)));
    
    EXPECT_TRUE(hasPriority<Mult>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Mult>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Mult>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Mult>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Mult>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Mult>(Token("exp", TAlphaNumeric)));
    
    EXPECT_TRUE(hasPriority<Pow>(Token("sin", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Pow>(Token("cos", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Pow>(Token("tan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Pow>(Token("ctan", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Pow>(Token("ln", TAlphaNumeric)));
    EXPECT_TRUE(hasPriority<Pow>(Token("exp", TAlphaNumeric)));
}

TEST_F(FX_Rule, hasPriority_AdditionsVSVarsAndConst_AdditionsHavePriority) {
    EXPECT_FALSE(hasPriority<Sum>(Token("a", TAlphaNumeric)));
    EXPECT_FALSE(hasPriority<Sum>(Token("1", TNumeric)));
    EXPECT_FALSE(hasPriority<Sub>(Token("a", TAlphaNumeric)));
    EXPECT_FALSE(hasPriority<Sub>(Token("1", TNumeric)));
}

TEST_F(FX_Rule, hasPriority_SameOperationOnBothSides_StillValid) {
    EXPECT_FALSE(hasPriority<Sum>(Token("+", TOperation)));
    EXPECT_FALSE(hasPriority<Sum>(Token("-", TOperation)));
    EXPECT_FALSE(hasPriority<Sub>(Token("+", TOperation)));
    EXPECT_FALSE(hasPriority<Sub>(Token("-", TOperation)));
    EXPECT_FALSE(hasPriority<Mult>(Token("*", TOperation)));
    EXPECT_FALSE(hasPriority<Mult>(Token("/", TOperation)));
    EXPECT_FALSE(hasPriority<Div>(Token("*", TOperation)));
    EXPECT_FALSE(hasPriority<Div>(Token("/", TOperation)));
}