/**
 * @file Tests for RuleMultRV. Handling of right hand argument of multiplication operation.
 *
 * @since 14.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleMultRV.h"
#include "Variable.h"
#include "Mult.h"
#include "Sub.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleMultRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
};

TEST_F(FX_RuleMultRV, apply_NormalRightValueForMultiplication_Reducable) {
    ParserStack stack;
    stack.push_back(createMult(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RuleMultRV ruleMultRV;
    EXPECT_TRUE(ruleMultRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PMult mult = SPointerCast<Mult>(*i);
    EXPECT_TRUE(isTypeOf<Mult>(mult));

    PVariable multRArg = SPointerCast<Variable>(mult->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(multRArg));
    EXPECT_STREQ("b", multRArg->name.c_str());
}

TEST_F(FX_RuleMultRV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("b"));
    stack.push_back(createMult());
    
    RuleMultRV ruleMultRV;
    EXPECT_FALSE(ruleMultRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleMultRV, apply_RightSideArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // a*-b
    stack.push_back(createMult(createVariable("a"), nullptr));
    stack.push_back(createSub(nullptr, createVariable("b")));

    RuleMultRV ruleMultRV;
    EXPECT_FALSE(ruleMultRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleMultRV, apply_MultiplicatioWithoutLeftArgument_ParsingException) {
    ParserStack stack;

    // *a
    stack.push_back(createMult());
    stack.push_back(createVariable("a"));
    
    RuleMultRV ruleMultRV;
    EXPECT_THROW(ruleMultRV.apply(stack, lookAheadToken()), ParsingException);
}