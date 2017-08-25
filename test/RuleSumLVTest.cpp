/**
 * @file Tests for RuleSumLV (lft value summation rule).
 *
 * @since 26.07.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleSumLV.h"
#include "Variable.h"
#include "Sum.h"

class FX_RuleSumLV : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    shared_ptr<Expression> createVariable(const string name) const {
        return make_shared<Variable>(name);
    }

    shared_ptr<Expression> createSum() const {
        return make_shared<Sum>();
    }
};

TEST_F(FX_RuleSumLV, apply_SimpleSummation_Reducable) {

    ParserStack stack;
    stack.push_back(createVariable("a"));
    stack.push_back(createSum());

    RuleSumLV ruleSumLV;
    EXPECT_TRUE(ruleSumLV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();

    shared_ptr<Sum> sum = dynamic_pointer_cast<Sum>(*i);
    EXPECT_TRUE(isTypeOf<Sum>(sum));

    shared_ptr<Variable> sumLArg = dynamic_pointer_cast<Variable>(sum->lArg);
    EXPECT_TRUE(isTypeOf<Variable>(sumLArg));
    EXPECT_STREQ("a", sumLArg->name.c_str());
}

TEST_F(FX_RuleSumLV, apply_SimpleSummation_NotReducable) {
    ParserStack stack;

    stack.push_back(createSum());
    stack.push_back(createVariable("a"));

    RuleSumLV ruleSumLV;
    EXPECT_FALSE(ruleSumLV.apply(stack, Token("NA", TNoToken)));

    ParserStack::const_iterator i = stack.begin();
    EXPECT_TRUE(isTypeOf<Sum>(*i));
    ++i;
    EXPECT_TRUE(isTypeOf<Variable>(*i));
}

TEST_F(FX_RuleSumLV, apply_SummationOperationWithoutArgument_NotReduced) {
    ParserStack stack;

    // ++a
    stack.push_back(createSum());
    stack.push_back(createSum());
    stack.push_back(createVariable("a"));

    RuleSumLV ruleSumLV;
    EXPECT_FALSE(ruleSumLV.apply(stack, Token("NA", TNoToken)));
}
