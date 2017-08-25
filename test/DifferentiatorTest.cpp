/**
 * @file Tests for Differentior.
 *
 * @since 25.08.2017
 * @author agor
 */

#include <gtest/gtest.h>
#include <list>
#include <string>
#include <memory>

#include "Differentiator.h"
#include "Variable.h"
#include "Constant.h"
#include "Sum.h"
#include "Sub.h"
#include "Mult.h"
#include "Div.h"

class FX_Differentiator : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }

    shared_ptr<Expression> createVariable(const string name) const {
        return make_shared<Variable>(name);
    }

    shared_ptr<Expression> createConstant(const string val) const {
        return make_shared<Constant>(val);
    }

    shared_ptr<Expression> createSum(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sum> sum = make_shared<Sum>();
        sum->lArg = lArg;
        sum->rArg = rArg;
        return sum;
    }

    shared_ptr<Expression> createSub(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Sub> sub = make_shared<Sub>();
        sub->lArg = lArg;
        sub->rArg = rArg;
        return sub;
    }

    shared_ptr<Expression> createMult(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Mult> mult = make_shared<Mult>();
        mult->lArg = lArg;
        mult->rArg = rArg;
        return mult;
    }

    shared_ptr<Expression> createDiv(shared_ptr<Expression> lArg, shared_ptr<Expression> rArg) const {
        shared_ptr<Div> div = make_shared<Div>();
        div->lArg = lArg;
        div->rArg = rArg;
        return div;
    }
    
    shared_ptr<Expression> createSin(shared_ptr<Expression> arg) const {
        shared_ptr<Sin> sin = make_shared<Sin>();
        sin->arg = arg;
        return sin;
    }
};

TEST_F(FX_Differentiator, visit_Constant_ZeroConstant) {
    shared_ptr<Expression> exp = this->createConstant("42");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    shared_ptr<Constant> difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("0", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotInitializedConstant_TraverseException) {
    shared_ptr<Expression> exp = this->createConstant("");
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_DifferentiatedVariable_OneConstant) {
    shared_ptr<Expression> exp = this->createVariable("x");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    shared_ptr<Constant> difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("1", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotDifferentiatedVariable_ZeroConstant) {
    shared_ptr<Expression> exp = this->createVariable("a");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    shared_ptr<Constant> difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("0", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotInitializedVariable_TraverseException) {
    shared_ptr<Expression> exp = this->createVariable("");
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Summation_Summation) {
    shared_ptr<Expression> exp = this->createSum(this->createConstant("42"), this->createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(difExp));
    
    shared_ptr<Sum> difExpTyped = dynamic_pointer_cast<Sum>(difExp);
    shared_ptr<Constant> sumL = dynamic_pointer_cast<Constant>(difExpTyped->lArg);
    ASSERT_STREQ("0", sumL->value.c_str());
    shared_ptr<Constant> sumR = dynamic_pointer_cast<Constant>(difExpTyped->rArg);
    ASSERT_STREQ("1", sumR->value.c_str());
}

TEST_F(FX_Differentiator, visit_IncompleteSummation_TraverseException) {
    shared_ptr<Expression> exp = this->createSum(nullptr, this->createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Subtraction_Subtraction) {
    shared_ptr<Expression> exp = this->createSub(this->createConstant("42"), this->createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sub>(difExp));
    
    shared_ptr<Sub> difExpTyped = dynamic_pointer_cast<Sub>(difExp);
    shared_ptr<Constant> subL = dynamic_pointer_cast<Constant>(difExpTyped->lArg);
    ASSERT_STREQ("0", subL->value.c_str());
    shared_ptr<Constant> subR = dynamic_pointer_cast<Constant>(difExpTyped->rArg);
    ASSERT_STREQ("1", subR->value.c_str());
}

TEST_F(FX_Differentiator, visit_IncompleteSubtraction_TraverseException) {
    shared_ptr<Expression> exp = this->createSub(nullptr, this->createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Division_QuotientRuleApplied) {
    shared_ptr<Expression> exp = this->createDiv(this->createVariable("a"), this->createVariable("b"));
    
    Differentiator differentiator("a");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    shared_ptr<Expression> difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Div>(difExp));
    
    shared_ptr<Div> difExpTyped = dynamic_pointer_cast<Div>(difExp);
    
    ASSERT_TRUE(isTypeOf<Sub>(difExpTyped->lArg));
    shared_ptr<Sub> divident = dynamic_pointer_cast<Sub>(difExpTyped->lArg);
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->lArg));
    shared_ptr<Mult> multL = dynamic_pointer_cast<Mult>(divident->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_TRUE(isTypeOf<Variable>(multL->rArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(multL->lArg)->value.c_str());
    ASSERT_STREQ("b", dynamic_pointer_cast<Variable>(multL->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->rArg));
    shared_ptr<Mult> multR = dynamic_pointer_cast<Mult>(divident->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(multR->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(multR->rArg));
    ASSERT_STREQ("a", dynamic_pointer_cast<Variable>(multR->lArg)->name.c_str());
    ASSERT_STREQ("0", dynamic_pointer_cast<Constant>(multR->rArg)->value.c_str());
    
    shared_ptr<Pow> divisor = dynamic_pointer_cast<Pow>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(divisor->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(divisor->rArg));
    ASSERT_STREQ("b", dynamic_pointer_cast<Variable>(divisor->lArg)->name.c_str());
    ASSERT_STREQ("2", dynamic_pointer_cast<Constant>(divisor->rArg)->value.c_str());
}

TEST_F(FX_Differentiator, visit_DivisionOperationIsIncoplete_TraverseException) {
    shared_ptr<Expression> exp = this->createDiv(this->createVariable("a"), nullptr);
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}