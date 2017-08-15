/**
 * @file Tests for RuleDivRV. Handling of right hand argument of division operation.
 *
 * @since 15.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleDivRV.h"
#include "Variable.h"
#include "Div.h"
#include "Sub.h"

class FX_RuleDivRV : public testing::Test {
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

    shared_ptr<Expression> createDiv() const {
        return make_shared<Div>();
    }

    shared_ptr<Expression> createDiv(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Div> div = make_shared<Div>();
        div->lArg = lArg;
        div->rArg = rArg;
        return div;
    }

    shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sub> sub = make_shared<Sub>();
        sub->lArg = lArg;
        sub->rArg = rArg;
        return sub;
    }
};

TEST_F(FX_RuleDivRV, apply_NormalRightValueForDivision_Reducable) {
    ParserStack stack;
    stack.push_back(createDiv(createVariable("a"), nullptr));
    stack.push_back(createVariable("b"));

    RuleDivRV ruleDivRV;
    EXPECT_TRUE(ruleDivRV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Div> div = dynamic_pointer_cast<Div>(*i);
    EXPECT_EQ(EDiv, div->type);

    shared_ptr<Variable> divRArg = dynamic_pointer_cast<Variable>(div->rArg);
    EXPECT_EQ(EVariable, divRArg->type);
    EXPECT_STREQ("b", divRArg->name.c_str());
}

TEST_F(FX_RuleDivRV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;
    stack.push_back(createVariable("b"));
    stack.push_back(createDiv());
    
    RuleDivRV ruleDivRV;
    EXPECT_FALSE(ruleDivRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivRV, apply_RightSideArgumentIsIncomplete_NotReducable) {
    ParserStack stack;

    // a/-b
    stack.push_back(createDiv(createVariable("a"), nullptr));
    stack.push_back(createSub(nullptr, createVariable("b")));

    RuleDivRV ruleDivRV;
    EXPECT_FALSE(ruleDivRV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivRV, apply_DivisionWithoutLeftArgument_ParsingException) {
    ParserStack stack;

    // /a
    stack.push_back(createDiv());
    stack.push_back(createVariable("a"));
    
    RuleDivRV ruleDivRV;
    EXPECT_THROW(ruleDivRV.apply(stack, lookAheadToken()), ParsingException);
}