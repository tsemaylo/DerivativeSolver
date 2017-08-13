/**
 * @file Tests for RuleSubLV (lft value summation rule).
 *
 * @since 26.07.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleSubLV.h"
#include "Variable.h"
#include "Sub.h"


class FX_RuleSubLV: public testing::Test {
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

TEST_F(FX_RuleSubLV, apply_SimpleSubtraction_Reducable) {
	
	ParserStack stack;
	stack.push_back(createVariable("a"));
	stack.push_back(createSub());
	
	RuleSubLV ruleSubLV;
	EXPECT_TRUE(ruleSubLV.apply(stack, lookAheadToken()));
	
	ParserStack::const_iterator i=stack.begin();
	
	shared_ptr<Sub> sub=dynamic_pointer_cast<Sub>(*i);
	EXPECT_EQ(ESub ,sub->type);
	
	shared_ptr<Variable> subLArg= dynamic_pointer_cast<Variable>(sub->lArg);
	EXPECT_EQ(EVariable ,subLArg->type);
	EXPECT_STREQ("a" ,subLArg->name.c_str());
}

TEST_F(FX_RuleSubLV, apply_SimpleSubtraction_NotReducable) {
	ParserStack stack;
	
	stack.push_back(createSub());
	stack.push_back(createVariable("a"));
	
	RuleSubLV ruleSubLV;
	EXPECT_FALSE(ruleSubLV.apply(stack, lookAheadToken()));
	
	ParserStack::const_iterator i=stack.begin();
	EXPECT_EQ(ESub ,dynamic_pointer_cast<Sub>(*i)->type);
	++i;
	EXPECT_EQ(EVariable ,dynamic_pointer_cast<Variable>(*i)->type);
}


TEST_F(FX_RuleSubLV, apply_SummationOperatirWithoutArgument_ParsingException) {
	ParserStack stack;
	
	// --a
	stack.push_back(createSub());
	stack.push_back(createSub());
	stack.push_back(createVariable("a"));
	
	RuleSubLV ruleSubLV;
	EXPECT_THROW(ruleSubLV.apply(stack, lookAheadToken()), ParsingException);
}
