/**
 * @file Test cases for RulePowLV (left value of exponentation rule).
 *
 * @since 16.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RulePowLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Pow.h"

class FX_RulePowLV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("NA", TNoToken);
    }
    
    Token lookAheadToken(string value, TokenType type) const {
        return Token(value, type);
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
    
    shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sum> sum = make_shared<Sum>();
        sum->lArg = lArg;
        sum->rArg = rArg;
        return sum;
    }
};

TEST_F(FX_RulePowLV, apply_LeftValueOfExponentation_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createPow());

    RulePowLV rulePowLV;
    EXPECT_TRUE(rulePowLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Pow> pow = dynamic_pointer_cast<Pow>(*i);
    EXPECT_TRUE(isTypeOf<Pow>(pow));

    shared_ptr<Variable> powLArg = dynamic_pointer_cast<Variable>(pow->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(powLArg));
    EXPECT_STREQ("a", powLArg->name.c_str());
}

TEST_F(FX_RulePowLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createPow());
    stack.push_back(createVariable("a"));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Pow>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RulePowLV, apply_ExponentationOperationIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b^c)
    stack.push_back(createVariable("a"));
    stack.push_back(createPow(createVariable("b"), createVariable("c")));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RulePowLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a^b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createPow());
    stack.push_back(createVariable("b"));

    RulePowLV rulePowLV;
    EXPECT_FALSE(rulePowLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
