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

#include "RuleSumRV.h"
#include "Variable.h"
#include "Sum.h"


class FX_RuleSumRV: public testing::Test {
protected:
	virtual void SetUp() {
	}
	
	virtual void TearDown() {
	}
	
	shared_ptr<Expression> createVariable(const string name) const{
		return make_shared<Variable>(name);
	}
	shared_ptr<Expression> createSum() const{
		return make_shared<Sum>();
	}
};

TEST_F(FX_RuleSumRV, apply_SimpleSummation_Reducable) {
	
	ParserStack stack;
	shared_ptr<Sum> stackSum=dynamic_pointer_cast<Sum>(createSum());
	stackSum->lArg=createVariable("b");
	stack.push_back(stackSum);
	stack.push_back(createVariable("a"));
	
	RuleSumRV ruleSumRV;
	EXPECT_TRUE(ruleSumRV.apply(stack, Token("NA", TNoToken)));
	
	ParserStack::const_iterator i=stack.begin();
	
	shared_ptr<Sum> sum=dynamic_pointer_cast<Sum>(*i);
	EXPECT_EQ(ESum ,sum->type);
	
	shared_ptr<Variable> sumRArg= dynamic_pointer_cast<Variable>(sum->rArg);
	EXPECT_EQ(EVariable ,sumRArg->type);
	EXPECT_STREQ("a" ,sumRArg->name.c_str());
}

TEST_F(FX_RuleSumRV, apply_SummationWithoutLeftArgument_Reducable) {
	
	ParserStack stack;
	stack.push_back(createSum());
	stack.push_back(createVariable("a"));
	
	RuleSumRV ruleSumRV;
	EXPECT_TRUE(ruleSumRV.apply(stack, Token("NA", TNoToken)));
	
	ParserStack::const_iterator i=stack.begin();
	
	shared_ptr<Variable> varA=dynamic_pointer_cast<Variable>(*i);
	EXPECT_EQ(EVariable ,varA->type);
	EXPECT_STREQ("a" ,varA->name.c_str());
}

TEST_F(FX_RuleSumRV, apply_SimpleSummation_NotReducable) {
	ParserStack stack;
	stack.push_back(createVariable("a"));
	stack.push_back(createSum());
	
	RuleSumRV ruleSumRV;
	EXPECT_FALSE(ruleSumRV.apply(stack, Token("NA", TNoToken)));
	
	EXPECT_EQ(2, stack.size());
	
	ParserStack::const_iterator i=stack.begin();
	EXPECT_EQ(EVariable ,dynamic_pointer_cast<Variable>(*i)->type);
	++i;
	EXPECT_EQ(ESum ,dynamic_pointer_cast<Sum>(*i)->type);
}

TEST_F(FX_RuleSumRV, apply_IncompleteExpressionOnTheRight_ParsingException) {
	
	ParserStack stack;
	// a++
	stack.push_back(createVariable("a"));
	stack.push_back(createSum());
	stack.push_back(createSum());
	
	RuleSumRV ruleSumRV;
	EXPECT_THROW(ruleSumRV.apply(stack, Token("NA", TNoToken)), ParsingException);
}
