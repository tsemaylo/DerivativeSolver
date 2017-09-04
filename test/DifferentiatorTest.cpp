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

#include "ExpressionFactory.h"

class FX_Differentiator : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_Differentiator, visit_Constant_ZeroConstant) {
    PConstant exp = createConstant("42");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("0", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotInitializedConstant_TraverseException) {
    PConstant exp = createConstant("");
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_DifferentiatedVariable_OneConstant) {
    PVariable exp = createVariable("x");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("1", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotDifferentiatedVariable_ZeroConstant) {
    PVariable exp = createVariable("a");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = dynamic_pointer_cast<Constant>(difExp);
    
    ASSERT_STREQ("0", difExpTyped->value.c_str());
}

TEST_F(FX_Differentiator, visit_NotInitializedVariable_TraverseException) {
    PVariable exp = createVariable("");
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Summation_Summation) {
    PSum exp = createSum(createConstant("42"), createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(difExp));
    
    PSum difExpTyped = dynamic_pointer_cast<Sum>(difExp);
    PConstant sumL = dynamic_pointer_cast<Constant>(difExpTyped->lArg);
    ASSERT_STREQ("0", sumL->value.c_str());
    PConstant sumR = dynamic_pointer_cast<Constant>(difExpTyped->rArg);
    ASSERT_STREQ("1", sumR->value.c_str());
}

TEST_F(FX_Differentiator, visit_IncompleteSummation_TraverseException) {
    PSum exp = createSum(nullptr, createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Subtraction_Subtraction) {
    PSub exp = createSub(createConstant("42"), createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sub>(difExp));
    
    PSub difExpTyped = dynamic_pointer_cast<Sub>(difExp);
    PConstant subL = dynamic_pointer_cast<Constant>(difExpTyped->lArg);
    ASSERT_STREQ("0", subL->value.c_str());
    PConstant subR = dynamic_pointer_cast<Constant>(difExpTyped->rArg);
    ASSERT_STREQ("1", subR->value.c_str());
}

TEST_F(FX_Differentiator, visit_IncompleteSubtraction_TraverseException) {
    PSub exp = createSub(nullptr, createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Division_QuotientRuleApplied) {
    PDiv exp = createDiv(createVariable("a"), createVariable("b"));
    
    Differentiator differentiator("a");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Div>(difExp));
    
    PDiv difExpTyped = dynamic_pointer_cast<Div>(difExp);
    
    ASSERT_TRUE(isTypeOf<Sub>(difExpTyped->lArg));
    PSub divident = dynamic_pointer_cast<Sub>(difExpTyped->lArg);
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->lArg));
    PMult multL = dynamic_pointer_cast<Mult>(divident->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_TRUE(isTypeOf<Variable>(multL->rArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(multL->lArg)->value.c_str());
    ASSERT_STREQ("b", dynamic_pointer_cast<Variable>(multL->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->rArg));
    PMult multR = dynamic_pointer_cast<Mult>(divident->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(multR->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(multR->rArg));
    ASSERT_STREQ("a", dynamic_pointer_cast<Variable>(multR->lArg)->name.c_str());
    ASSERT_STREQ("0", dynamic_pointer_cast<Constant>(multR->rArg)->value.c_str());
    
    PPow divisor = dynamic_pointer_cast<Pow>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(divisor->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(divisor->rArg));
    ASSERT_STREQ("b", dynamic_pointer_cast<Variable>(divisor->lArg)->name.c_str());
    ASSERT_STREQ("2", dynamic_pointer_cast<Constant>(divisor->rArg)->value.c_str());
}

TEST_F(FX_Differentiator, visit_DivisionOperationIsIncoplete_TraverseException) {
    PDiv exp = createDiv(createVariable("a"), nullptr);
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Multiplication_ProductRuleApplied) {
    PMult exp = createMult(createVariable("a"), createVariable("b"));
    
    Differentiator differentiator("a");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(difExp));
    PSum difExpTyped=dynamic_pointer_cast<Sum>(difExp);
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->lArg));
    PMult multL = dynamic_pointer_cast<Mult>(difExpTyped->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_TRUE(isTypeOf<Variable>(multL->rArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(multL->lArg)->value.c_str());
    ASSERT_STREQ("b", dynamic_pointer_cast<Variable>(multL->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult multR = dynamic_pointer_cast<Mult>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(multR->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(multR->rArg));
    ASSERT_STREQ("a", dynamic_pointer_cast<Variable>(multR->lArg)->name.c_str());
    ASSERT_STREQ("0", dynamic_pointer_cast<Constant>(multR->rArg)->value.c_str());
}

TEST_F(FX_Differentiator, visit_MultiplicationOperationIsIncoplete_TraverseException) {
    PMult exp = createMult(nullptr, createVariable("a"));
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Exponentiation_GeneralizedPowerRuleApplied) {
    PPow exp = createPow(createVariable("x"), createConstant("3"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=dynamic_pointer_cast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Pow>(difExpTyped->lArg));
    PPow pow=dynamic_pointer_cast<Pow>(difExpTyped->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(pow->lArg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(pow->lArg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_STREQ("3", dynamic_pointer_cast<Constant>(pow->rArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Sum>(difExpTyped->rArg));
    PSum sum=dynamic_pointer_cast<Sum>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Mult>(sum->lArg));
    PMult multL=dynamic_pointer_cast<Mult>(sum->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(multL->lArg)->value.c_str());
    ASSERT_TRUE(isTypeOf<Div>(multL->rArg));
    PDiv div=dynamic_pointer_cast<Div>(multL->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(div->lArg));
    ASSERT_STREQ("3", dynamic_pointer_cast<Constant>(div->lArg)->value.c_str());
    ASSERT_TRUE(isTypeOf<Variable>(div->rArg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(div->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(sum->rArg));
    PMult multR=dynamic_pointer_cast<Mult>(sum->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(multR->lArg));
    ASSERT_STREQ("0", dynamic_pointer_cast<Constant>(multR->lArg)->value.c_str());
    ASSERT_TRUE(isTypeOf<Ln>(multR->rArg));
    PLn ln=dynamic_pointer_cast<Ln>(multR->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(ln->arg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(ln->arg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_ExponentiationOperationIsIncoplete_TraverseException) {
    PExpression exp = createMult(nullptr, createVariable("a"));
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_SineFunction_ChainAndTrigonometricRulesApplied) {
    PSin exp = createSin(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=dynamic_pointer_cast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(difExpTyped->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Cos>(difExpTyped->rArg));
    PCos cos=dynamic_pointer_cast<Cos>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(cos->arg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(cos->arg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_SineFunctionWothoutArgument_TraverseException) {
    PSin exp = createSin(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_CosineFunction_ChainAndTrigonometricRulesApplied) {
    PCos exp = createCos(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=dynamic_pointer_cast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(difExpTyped->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult negatedSine=dynamic_pointer_cast<Mult>(difExpTyped->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(negatedSine->lArg));
    ASSERT_STREQ("-1", dynamic_pointer_cast<Constant>(negatedSine->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Sin>(negatedSine->rArg));
    PSin sin=dynamic_pointer_cast<Sin>(negatedSine->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(sin->arg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(sin->arg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_CosineFunctionWothoutArgument_TraverseException) {
    PCos exp = createCos(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_TangentFunction_ChainAndTrigonometricRulesApplied) {
    PTan exp = createTan(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=dynamic_pointer_cast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(difExpTyped->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Sum>(difExpTyped->rArg));
    PSum tangentSum=dynamic_pointer_cast<Sum>(difExpTyped->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(tangentSum->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(tangentSum->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Pow>(tangentSum->rArg));
    PPow pow=dynamic_pointer_cast<Pow>(tangentSum->rArg);
    ASSERT_TRUE(isTypeOf<Tan>(pow->lArg));
    PTan tan=dynamic_pointer_cast<Tan>(pow->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(tan->arg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(tan->arg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_STREQ("2", dynamic_pointer_cast<Constant>(pow->rArg)->value.c_str());
}

TEST_F(FX_Differentiator, visit_TangentFunctionWithoutArgument_TraverseException) {
    PTan exp = createTan(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_CotangentFunction_ChainAndTrigonometricRulesApplied) {
    PCtan exp = createCtan(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=dynamic_pointer_cast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(difExpTyped->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult negated=dynamic_pointer_cast<Mult>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(negated->lArg));
    ASSERT_STREQ("-1", dynamic_pointer_cast<Constant>(negated->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Sum>(negated->rArg));
    PSum cotangentSum=dynamic_pointer_cast<Sum>(negated->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(cotangentSum->lArg));
    ASSERT_STREQ("1", dynamic_pointer_cast<Constant>(cotangentSum->lArg)->value.c_str());
    
    ASSERT_TRUE(isTypeOf<Pow>(cotangentSum->rArg));
    PPow pow=dynamic_pointer_cast<Pow>(cotangentSum->rArg);
    ASSERT_TRUE(isTypeOf<Ctan>(pow->lArg));
    PCtan ctan=dynamic_pointer_cast<Ctan>(pow->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(ctan->arg));
    ASSERT_STREQ("x", dynamic_pointer_cast<Variable>(ctan->arg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_STREQ("2", dynamic_pointer_cast<Constant>(pow->rArg)->value.c_str());
}

TEST_F(FX_Differentiator, visit_CotangentFunctionWithoutArgument_TraverseException) {
    PCtan exp = createCtan(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}