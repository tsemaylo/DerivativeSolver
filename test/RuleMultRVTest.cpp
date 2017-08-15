/**
 * @file Tests for RuleMultRV. Handling of right hand argument of multiplication operation.
 *
 * @since 14.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleMultRV.h"
#include "Variable.h"
#include "Mult.h"
#include "Sub.h"

class FX_RuleMultRV : public testing::Test {
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

    shared_ptr<Expression> createMult() const {
        return make_shared<Mult>();
    }

    shared_ptr<Expression> createMult(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Mult> mult = make_shared<Mult>();
        mult->lArg = lArg;
        mult->rArg = rArg;
        return mult;
    }

    shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sub> sub = make_shared<Sub>();
        sub->lArg = lArg;
        sub->rArg = rArg;
        return sub;
    }
};

TEST_F(FX_RuleMultRV, apply_NormalRightValueForMultiplication_Reducable) {
    ParserStack stack;
    stack.push_back(createMult(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RuleMultRV ruleMultRV;
    EXPECT_TRUE(ruleMultRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Mult> mult = dynamic_pointer_cast<Mult>(*i);
    EXPECT_EQ(EMult, mult->type);

    shared_ptr<Variable> multRArg = dynamic_pointer_cast<Variable>(mult->rArg);
    EXPECT_EQ(EVariable, multRArg->type);
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