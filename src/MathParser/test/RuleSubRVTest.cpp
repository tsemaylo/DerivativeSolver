/**
 * @file Tests for RuleSumRV (process expression on the right sde of summation op).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleSubRV.h"


#include "Constant.h"
#include "Variable.h"
#include "Sub.h"
#include "Mult.h"
#include "Token.h"
#include "ExpressionFactory.h"

class FX_RuleSubRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
    
    Token lookAheadToken() {
        return Token("NA", TNoToken);
    }
    
    Token lookAheadToken(string value, TokenType type) {
        return Token(value, type);
    }
};

TEST_F(FX_RuleSubRV, apply_SimpleSubtraction_Reducable) {
    ParserStack stack;
    PSub stackSub = SPointerCast<Sub>(createSub());
    stackSub->lArg = createVariable("b");
    stack.push_back(stackSub);
    stack.push_back(createVariable("a"));

    RuleSubRV ruleSubRV;
    EXPECT_TRUE(ruleSubRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PSub sub = SPointerCast<Sub>(*i);
    EXPECT_TRUE(isTypeOf<Sub>(sub));

    PVariable subRArg = SPointerCast<Variable>(sub->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(subRArg));
    EXPECT_STREQ("a", subRArg->name.c_str());
}

TEST_F(FX_RuleSubRV, apply_SubtractionWithoutLeftArgument_Reducable) {

    ParserStack stack;
    stack.push_back(createSub());
    stack.push_back(createVariable("a"));

    RuleSubRV ruleSubRV;
    EXPECT_TRUE(ruleSubRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    EXPECT_TRUE(isTypeOf<Mult>((*i)));

    PMult mult = SPointerCast<Mult>(*i);
    EXPECT_TRUE(isTypeOf<Constant>(mult->lArg));
    EXPECT_TRUE(isTypeOf<Variable>(mult->rArg));
}

TEST_F(FX_RuleSubRV, apply_SimpleSummation_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createSub());

    RuleSubRV ruleSubRV;
    EXPECT_FALSE(ruleSubRV.apply(stack, lookAheadToken()));

    EXPECT_EQ(2, stack.size());

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Variable>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Sub>(*i));
}

TEST_F(FX_RuleSubRV, apply_IncompleteExpressionOnTheRight_NotReduced) {
    ParserStack stack;
    // a-b*c
    stack.push_back(createSub(createVariable("a"), nullptr));
    stack.push_back(createMult(createVariable("b"), nullptr));

    RuleSubRV ruleSubRV;
    EXPECT_FALSE(ruleSubRV.apply(stack, lookAheadToken("c", TAlphaNumeric)));
}
