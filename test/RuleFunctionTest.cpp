/**
 * @file Tests for RuleFunction. Handling of right hand argument of division operation.
 *
 * @since 15.08.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleFunction.h"
#include "Variable.h"
#include "Sin.h"

class FX_RuleFunction : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    Token lookAheadToken() const {
        return Token("(", TGroupBracket);
    }

    shared_ptr<Expression> createVariable(const string name) const {
        return make_shared<Variable>(name);
    }

    shared_ptr<Expression> createSin() const {
        return make_shared<Sin>();
    }
    
    shared_ptr<Expression> createSin(shared_ptr<Expression> arg) const {
        shared_ptr<Sin> sin=make_shared<Sin>();
        sin->arg=arg;
        return sin;
    }
    
    shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sum> sum = make_shared<Sum>();
        sum->lArg = lArg;
        sum->rArg = rArg;
        return sum;
    }

};

TEST_F(FX_RuleFunction, apply_SinNormalArgumentAssignment_Reducable) {
    ParserStack stack;
    stack.push_back(createSin());
    stack.push_back(createVariable("x"));

    RuleFunction<Sin> ruleFuncSin;
    EXPECT_TRUE(ruleFuncSin.apply(stack, lookAheadToken()));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Sin> sin = dynamic_pointer_cast<Sin>(*i);
    EXPECT_TRUE(isTypeOf<Sin>(sin));

    shared_ptr<Variable> sinArg = dynamic_pointer_cast<Variable>(sin->arg);
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