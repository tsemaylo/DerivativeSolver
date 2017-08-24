/**
 * @file Tests for RulePowRV. Handling of right hand argument of exponentation operation.
 *
 * @since 16.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RulePowRV.h"
#include "Variable.h"
#include "Pow.h"
#include "Sub.h"

class FX_RulePowRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }

    shared_ptr<Expression> createVariable(const string name) const {
        return make_shared<Variable>(name);
    }

    shared_ptr<Expression> createPow() const {
        return make_shared<Pow>();
    }

    shared_ptr<Expression> createPow(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Pow> pow = make_shared<Pow>();
        pow->lArg = lArg;
        pow->rArg = rArg;
        return pow;
    }

    shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sub> sub = make_shared<Sub>();
        sub->lArg = lArg;
        sub->rArg = rArg;
        return sub;
    }
};

TEST_F(FX_RulePowRV, apply_NormalRightValueForExponentationOperation_Reducable) {
    ParserStack stack;
    stack.push_back(createPow(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RulePowRV rulePowRV;
    EXPECT_TRUE(rulePowRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Pow> pow = dynamic_pointer_cast<Pow>(*i);
    EXPECT_TRUE(isTypeOf<Pow>(pow));

    shared_ptr<Variable> powRArg = dynamic_pointer_cast<Variable>(pow->rArg);
    EXPECT_TRUE(isTypeOf<Variable>(powRArg));
    EXPECT_STREQ("b", powRArg->name.c_str());
}

TEST_F(FX_RulePowRV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("b"));
    stack.push_back(createPow());
    
    RulePowRV rulePowRV;
    EXPECT_FALSE(rulePowRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowRV, apply_RightSideArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // a^-b
    stack.push_back(createPow(createVariable("a"), nullptr));
    stack.push_back(createSub(nullptr, createVariable("b")));

    RulePowRV rulePowRV;
    EXPECT_FALSE(rulePowRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowRV, apply_ExponentationOperationWithoutLeftArgument_ParsingException) {
    ParserStack stack;

    // ^a
    stack.push_back(createPow());
    stack.push_back(createVariable("a"));
    
    RulePowRV rulePowRV;
    EXPECT_THROW(rulePowRV.apply(stack, lookAheadToken()), ParsingException);
}