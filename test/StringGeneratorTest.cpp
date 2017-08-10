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

#include "StringGenerator.h"
#include "Variable.h"
#include "Constant.h"
#include "Sum.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"


class FX_StringGenerator: public testing::Test {
protected:
	virtual void SetUp() {
	}
	
	virtual void TearDown() {
	}
	
	shared_ptr<Expression> createVariable(const string name) const{
		return make_shared<Variable>(name);
	}
	shared_ptr<Expression> createConstant(const string val) const{
		return make_shared<Constant>(val);
	}
	shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const{
		shared_ptr<Sum> sum=make_shared<Sum>();
		sum->lArg=lArg;
		sum->rArg=rArg;
		return sum;
	}
	shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const{
		shared_ptr<Sub> sub=make_shared<Sub>();
		sub->lArg=lArg;
		sub->rArg=rArg;
		return sub;
	}
	shared_ptr<Expression> createMult(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const{
		shared_ptr<Mult> mult=make_shared<Mult>();
		mult->lArg=lArg;
		mult->rArg=rArg;
		return mult;
	}
	shared_ptr<Expression> createDiv(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const{
		shared_ptr<Div> div=make_shared<Div>();
		div->lArg=lArg;
		div->rArg=rArg;
		return div;
	}
};

TEST_F(FX_StringGenerator, visit_SimpleCase_ok) {
	// a+5*b-c/2
	
	shared_ptr<Expression> varB=createVariable("b");
	shared_ptr<Expression> const5=createConstant("5");
	shared_ptr<Expression> mult=createMult(const5, varB);
	
	shared_ptr<Expression> varA=createVariable("a");
	shared_ptr<Expression> sum=createSum(varA, mult);
	
	shared_ptr<Expression> varC=createVariable("c");
	shared_ptr<Expression> const2=createConstant("2");
	shared_ptr<Expression> div=createDiv(varC, const2);
	
	shared_ptr<Expression> sub=createSub(sum, div);
	
	StringGenerator strGen;
	sub->traverse(strGen);
	ASSERT_STREQ("a+5*b-c/2", strGen.getLastVisitResult().c_str());
}
