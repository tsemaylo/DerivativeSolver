/**
 * @file Tests for RuleSumRV (process expression on the right sde of summation op).
 *
 * @since 26.07.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleSubRV.h"
#include "Constant.h"
#include "Variable.h"
#include "Sub.h"
#include "Mult.h"

class FX_RuleSubRV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    shared_ptr<Expression> createVariable(const string name) const {
        return make_shared<Variable>(name);
    }

    shared_ptr<Expression> createSub() const {
        return make_shared<Sub>();
    }
    
    shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sub> sub = make_shared<Sub>();
        sub->lArg = lArg;
        sub->rArg = rArg;
        return sub;
    }
    
    shared_ptr<Expression> createMult(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Mult> mult = make_shared<Mult>();
        mult->lArg = lArg;
        mult->rArg = rArg;
        return mult;
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
    shared_ptr<Sub> stackSub = dynamic_pointer_cast<Sub>(createSub());
    stackSub->lArg = createVariable("b");
    stack.push_back(stackSub);
    stack.push_back(createVariable("a"));

    RuleSubRV ruleSubRV;
    EXPECT_TRUE(ruleSubRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Sub> sub = dynamic_pointer_cast<Sub>(*i);
    EXPECT_TRUE(isTypeOf<Sub>(sub));

    shared_ptr<Variable> subRArg = dynamic_pointer_cast<Variable>(sub->rArg);
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

    shared_ptr<Mult> mult = dynamic_pointer_cast<Mult>(*i);
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
