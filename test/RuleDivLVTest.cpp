/**
 * @file Test cases for RuleDivLV (left value division rule).
 *
 * @since 15.08.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleDivLV.h"
#include "Variable.h"
#include "Sum.h"
#include "Div.h"

class FX_RuleDivLV : public testing::Test {
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

    shared_ptr<Expression> createDiv() const {
        return make_shared<Div>();
    }
    
    shared_ptr<Expression> createDiv(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Div> div = make_shared<Div>();
        div->lArg = lArg;
        div->rArg = rArg;
        return div;
    }
    
    shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sum> sum = make_shared<Sum>();
        sum->lArg = lArg;
        sum->rArg = rArg;
        return sum;
    }
};

TEST_F(FX_RuleDivLV, apply_LeftValueDivision_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createDiv());

    RuleDivLV ruleDivLV;
    EXPECT_TRUE(ruleDivLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Div> div = dynamic_pointer_cast<Div>(*i);
    EXPECT_TRUE(isTypeOf<Div>(div));

    shared_ptr<Variable> divLArg = dynamic_pointer_cast<Variable>(div->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(divLArg));
    EXPECT_STREQ("a", divLArg->name.c_str());
}

TEST_F(FX_RuleDivLV, apply_RuleIsNotAppliable_NotReducable) {
    ParserStack stack;

    stack.push_back(createDiv());
    stack.push_back(createVariable("a"));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Div>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleDivLV, apply_DivisionIsAlreadyComplete_NotReducable) {
    ParserStack stack;

    // a(b/c)
    stack.push_back(createVariable("a"));
    stack.push_back(createDiv(createVariable("b"), createVariable("c")));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken()));
}

TEST_F(FX_RuleDivLV, apply_LeftHandArgumentIsNotComplete_NotReducable) {
    ParserStack stack;

    // +a/b
    stack.push_back(createSum(nullptr, createVariable("a")));
    stack.push_back(createDiv());
    stack.push_back(createVariable("b"));

    RuleDivLV ruleDivLV;
    EXPECT_FALSE(ruleDivLV.apply(stack, lookAheadToken("b", TAlphaNumeric)));
}
