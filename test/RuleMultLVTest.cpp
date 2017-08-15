/**
 * @file Test cases for RuleMultLV (left value division rule).
 *
 * @since 14.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleMultLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Mult.h"

class FX_RuleMultLV : public testing::Test {
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

    shared_ptr<Expression> createMult() const {
        return make_shared<Mult>();
    }
    
    shared_ptr<Expression> createMult(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Mult> mult = make_shared<Mult>();
        mult->lArg = lArg;
        mult->rArg = rArg;
        return mult;
    }
    
    shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sum> sum = make_shared<Sum>();
        sum->lArg = lArg;
        sum->rArg = rArg;
        return sum;
    }
};

TEST_F(FX_RuleMultLV, apply_LeftValueMultiplication_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createMult());

    RuleMultLV ruleMultLV;
    EXPECT_TRUE(ruleMultLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Mult> mult = dynamic_pointer_cast<Mult>(*i);
    EXPECT_EQ(EMult, mult->type);

    shared_ptr<Variable> multLArg = dynamic_pointer_cast<Variable>(mult->lArg);
    EXPECT_EQ(EVariable, multLArg->type);
    EXPECT_STREQ("a", multLArg->name.c_str());
}

TEST_F(FX_RuleMultLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createMult());
    stack.push_back(createVariable("a"));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_EQ(EMult, dynamic_pointer_cast<Mult>(*i)->type);
    ++i;
    EXPECT_EQ(EVariable, dynamic_pointer_cast<Variable>(*i)->type);
}

TEST_F(FX_RuleMultLV, apply_MultiplicationIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b*c)
    stack.push_back(createVariable("a"));
    stack.push_back(createMult(createVariable("b"), createVariable("c")));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleMultLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a*b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createMult());
    stack.push_back(createVariable("b"));

    RuleMultLV ruleMultLV;
    EXPECT_FALSE(ruleMultLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
