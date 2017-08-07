/**
 * @file Tests for RuleSumLV (lft value summation rule).
 *
 * @since 26.07.2016
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "RuleSumLV.h"
#include "Variable.h"
#include "Sum.h"


class FX_RuleSumLV: public testing::Test {
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

TEST_F(FX_RuleSumLV, apply_SimpleSummation_Reducable) {
	
	ParserStack stack;
	stack.push_back(createVariable("a"));
	stack.push_back(createSum());
	
	RuleSumLV ruleSumLV;
	ASSERT_TRUE(ruleSumLV.apply(stack));
	
	ParserStack::const_iterator i=stack.begin();
	
	shared_ptr<Sum> sum=dynamic_pointer_cast<Sum>(*i);
	ASSERT_EQ(ESum ,sum->type);
	
	shared_ptr<Variable> sumLArg= dynamic_pointer_cast<Variable>(sum->lArg);
	ASSERT_EQ(EVariable ,sumLArg->type);
	ASSERT_STREQ("a" ,sumLArg->name.c_str());
}

TEST_F(FX_RuleSumLV, apply_SimpleSummation_NotReducable) {
	ParserStack stack;
	
	stack.push_back(createSum());
	stack.push_back(createVariable("a"));
	
	RuleSumLV ruleSumLV;
	ASSERT_FALSE(ruleSumLV.apply(stack));
	
	ParserStack::const_iterator i=stack.begin();
	ASSERT_EQ(ESum ,dynamic_pointer_cast<Sum>(*i)->type);
	++i;
	ASSERT_EQ(EVariable ,dynamic_pointer_cast<Variable>(*i)->type);
}


TEST_F(FX_RuleSumLV, apply_SummationOperatirWithoutArgument_ParsingException) {
	ParserStack stack;
	
	// ++a
	stack.push_back(createSum());
	stack.push_back(createSum());
	stack.push_back(createVariable("a"));
	
	RuleSumLV ruleSumLV;
	ASSERT_THROW(ruleSumLV.apply(stack), ParsingException);
}