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
#include "Variable.h"
#include "Sub.h"
#include "Mult.h"


class FX_RuleSubRV: public testing::Test {
protected:
	virtual void SetUp() {
	}
	
	virtual void TearDown() {
	}
	
	shared_ptr<Expression> createVariable(const string name) const{
		return make_shared<Variable>(name);
	}
	shared_ptr<Expression> createSub() const{
		return make_shared<Sub>();
	}

	Token lookAheadToken(){
		return Token("NA", TNoToken);
	}
};

TEST_F(FX_RuleSubRV, apply_SimpleSubtraction_Reducable) {
	
	ParserStack stack;
	shared_ptr<Sub> stackSub=dynamic_pointer_cast<Sub>(createSub());
	stackSub->lArg=createVariable("b");
	stack.push_back(stackSub);
	stack.push_back(createVariable("a"));
	
	RuleSubRV ruleSubRV;
	EXPECT_TRUE(ruleSubRV.apply(stack, lookAheadToken()));
	
	ParserStack::const_iterator i=stack.begin();
	
	shared_ptr<Sub> sub=dynamic_pointer_cast<Sub>(*i);
	EXPECT_EQ(ESub ,sub->type);
	
	shared_ptr<Variable> subRArg= dynamic_pointer_cast<Variable>(sub->rArg);
	EXPECT_EQ(EVariable ,subRArg->type);
	EXPECT_STREQ("a" ,subRArg->name.c_str());
}

TEST_F(FX_RuleSubRV, apply_SubtractionWithoutLeftArgument_Reducable) {
	
	ParserStack stack;
	stack.push_back(createSub());
	stack.push_back(createVariable("a"));
	
	RuleSubRV ruleSubRV;
	EXPECT_TRUE(ruleSubRV.apply(stack, lookAheadToken()));
	
	ParserStack::const_iterator i=stack.begin();
	
	EXPECT_EQ(EMult ,(*i)->type);
	
	shared_ptr<Mult> mult=dynamic_pointer_cast<Mult>(*i);
	EXPECT_EQ(EConstant, mult->lArg->type);
	EXPECT_EQ(EVariable, mult->rArg->type);
}

TEST_F(FX_RuleSubRV, apply_SimpleSummation_NotReducable) {
	ParserStack stack;
	stack.push_back(createVariable("a"));
	stack.push_back(createSub());
	
	RuleSubRV ruleSubRV;
	EXPECT_FALSE(ruleSubRV.apply(stack, lookAheadToken()));
	
	EXPECT_EQ(2, stack.size());
	
	ParserStack::const_iterator i=stack.begin();
	EXPECT_EQ(EVariable ,dynamic_pointer_cast<Variable>(*i)->type);
	++i;
	EXPECT_EQ(ESub ,(*i)->type);
}

TEST_F(FX_RuleSubRV, apply_IncompleteExpressionOnTheRight_ParsingException) {
	
	ParserStack stack;
	// a--
	stack.push_back(createVariable("a"));
	stack.push_back(createSub());
	stack.push_back(createSub());
	
	RuleSubRV ruleSubRV;
	EXPECT_THROW(ruleSubRV.apply(stack, lookAheadToken()), ParsingException);
}
