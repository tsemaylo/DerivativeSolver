/**
 * @file Tests for RuleFunction. Handling of right hand argument of division operation.
 *
 * @since 15.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "RuleFunction.h"
#include "Variable.h"
#include "Sin.h"

#include "ExpressionFactory.h"

class FX_RuleFunction : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("(", TGroupBracket);
    }
};

TEST_F(FX_RuleFunction, apply_SinNormalArgumentAssignment_Reducable) {
    ParserStack stack;
    stack.push_back(createSin());
    stack.push_back(createVariable("x"));

    RuleFunction<Sin> ruleFuncSin;
    EXPECT_TRUE(ruleFuncSin.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    PSin sin = SPointerCast<Sin>(*i);
    EXPECT_TRUE(isTypeOf<Sin>(sin));

    PVariable sinArg = SPointerCast<Variable>(sin->arg);
    EXPECT_TRUE(isTypeOf<Variable>(sinArg));
    EXPECT_STREQ("x", sinArg->name.c_str());
}

TEST_F(FX_RuleFunction, apply_FunctionIsFull_NotReducable) {
    ParserStack stack;
    stack.push_back(createSin(createVariable("x")));
    stack.push_back(createVariable("a"));
    
    RuleFunction<Sin> ruleFuncSin;
    EXPECT_FALSE(ruleFuncSin.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleFunction, apply_ArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // sin(a+)
    stack.push_back(createSin());
    stack.push_back(createSum(createVariable("a"), nullptr));
    
    RuleFunction<Sin> ruleFuncSin;
    EXPECT_FALSE(ruleFuncSin.apply(stack, lookAheadToken()));
}