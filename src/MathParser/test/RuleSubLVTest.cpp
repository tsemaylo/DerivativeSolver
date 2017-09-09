/**
 * @file Tests for RuleSubLV (lft value subtraction rule).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleSubLV.h"
#include "Variable.h"
#include "Sub.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleSubLV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() {
        return Token("NA", TNoToken);
    }
};

TEST_F(FX_RuleSubLV, apply_SimpleSubtraction_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createSub());

    RuleSubLV ruleSubLV;
    EXPECT_TRUE(ruleSubLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PSub sub = SPointerCast<Sub>(*i);
    EXPECT_TRUE(isTypeOf<Sub>(sub));

    PVariable subLArg = SPointerCast<Variable>(sub->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(subLArg));
    EXPECT_STREQ("a", subLArg->name.c_str());
}

TEST_F(FX_RuleSubLV, apply_SimpleSubtraction_NotReducable) {
    ParserStack stack;

    stack.push_back(createSub());
    stack.push_back(createVariable("a"));

    RuleSubLV ruleSubLV;
    EXPECT_FALSE(ruleSubLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Sub>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleSubLV, apply_SubtractionOperationWithIncompleteLeftArgument_NotReduced) {
    ParserStack stack;

    // -a-b
    stack.push_back(createSub(nullptr, createVariable("a")));
    stack.push_back(createSub());
    stack.push_back(createVariable("b"));

    RuleSubLV ruleSubLV;
    EXPECT_FALSE(ruleSubLV.apply(stack, lookAheadToken()));
}
