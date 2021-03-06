/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file DifferentiatorTest.cpp
 * 
 * Tests for Differentior.
 *
 * @since 25.08.2017
 * @author agor
 */

#include <gtest/gtest.h>

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
    PConstant exp = createConstant(42.0);
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = SPointerCast<Constant>(difExp);
    
    ASSERT_DOUBLE_EQ(0, difExpTyped->value);
}

TEST_F(FX_Differentiator, visit_DifferentiatedVariable_OneConstant) {
    PVariable exp = createVariable("x");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = SPointerCast<Constant>(difExp);
    
    ASSERT_DOUBLE_EQ(1.0, difExpTyped->value);
}

TEST_F(FX_Differentiator, visit_NotDifferentiatedVariable_ZeroConstant) {
    PVariable exp = createVariable("a");
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(difExp));
    
    PConstant difExpTyped = SPointerCast<Constant>(difExp);
    
    ASSERT_DOUBLE_EQ(0, difExpTyped->value);
}

TEST_F(FX_Differentiator, visit_NotInitializedVariable_TraverseException) {
    PVariable exp = createVariable("");
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Summation_Summation) {
    PSum exp = createSum(createConstant(42.0), createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sum>(difExp));
    
    PSum difExpTyped = SPointerCast<Sum>(difExp);
    PConstant sumL = SPointerCast<Constant>(difExpTyped->lArg);
    ASSERT_DOUBLE_EQ(0.0, sumL->value);
    PConstant sumR = SPointerCast<Constant>(difExpTyped->rArg);
    ASSERT_DOUBLE_EQ(1.0, sumR->value);
}

TEST_F(FX_Differentiator, visit_IncompleteSummation_TraverseException) {
    PSum exp = createSum(nullptr, createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Subtraction_Subtraction) {
    PSub exp = createSub(createConstant(42.0), createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp=differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Sub>(difExp));
    
    PSub difExpTyped = SPointerCast<Sub>(difExp);
    PConstant subL = SPointerCast<Constant>(difExpTyped->lArg);
    ASSERT_DOUBLE_EQ(0.0, subL->value);
    PConstant subR = SPointerCast<Constant>(difExpTyped->rArg);
    ASSERT_DOUBLE_EQ(1.0, subR->value);
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
    
    PDiv difExpTyped = SPointerCast<Div>(difExp);
    
    ASSERT_TRUE(isTypeOf<Sub>(difExpTyped->lArg));
    PSub divident = SPointerCast<Sub>(difExpTyped->lArg);
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->lArg));
    PMult multL = SPointerCast<Mult>(divident->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_TRUE(isTypeOf<Variable>(multL->rArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(multL->lArg)->value);
    ASSERT_STREQ("b", SPointerCast<Variable>(multL->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(divident->rArg));
    PMult multR = SPointerCast<Mult>(divident->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(multR->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(multR->rArg));
    ASSERT_STREQ("a", SPointerCast<Variable>(multR->lArg)->name.c_str());
    ASSERT_DOUBLE_EQ(0.0, SPointerCast<Constant>(multR->rArg)->value);
    
    PPow divisor = SPointerCast<Pow>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(divisor->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(divisor->rArg));
    ASSERT_STREQ("b", SPointerCast<Variable>(divisor->lArg)->name.c_str());
    ASSERT_DOUBLE_EQ(2.0, SPointerCast<Constant>(divisor->rArg)->value);
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
    PSum difExpTyped=SPointerCast<Sum>(difExp);
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->lArg));
    PMult multL = SPointerCast<Mult>(difExpTyped->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_TRUE(isTypeOf<Variable>(multL->rArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(multL->lArg)->value);
    ASSERT_STREQ("b", SPointerCast<Variable>(multL->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult multR = SPointerCast<Mult>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(multR->lArg));
    ASSERT_TRUE(isTypeOf<Constant>(multR->rArg));
    ASSERT_STREQ("a", SPointerCast<Variable>(multR->lArg)->name.c_str());
    ASSERT_DOUBLE_EQ(0.0, SPointerCast<Constant>(multR->rArg)->value);
}

TEST_F(FX_Differentiator, visit_MultiplicationOperationIsIncoplete_TraverseException) {
    PMult exp = createMult(nullptr, createVariable("a"));
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_Exponentiation_GeneralizedPowerRuleApplied) {
    PPow exp = createPow(createVariable("x"), createConstant(3.0));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Pow>(difExpTyped->lArg));
    PPow pow=SPointerCast<Pow>(difExpTyped->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(pow->lArg));
    ASSERT_STREQ("x", SPointerCast<Variable>(pow->lArg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_DOUBLE_EQ(3.0, SPointerCast<Constant>(pow->rArg)->value);
    
    ASSERT_TRUE(isTypeOf<Sum>(difExpTyped->rArg));
    PSum sum=SPointerCast<Sum>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Mult>(sum->lArg));
    PMult multL=SPointerCast<Mult>(sum->lArg);
    ASSERT_TRUE(isTypeOf<Constant>(multL->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(multL->lArg)->value);
    ASSERT_TRUE(isTypeOf<Div>(multL->rArg));
    PDiv div=SPointerCast<Div>(multL->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(div->lArg));
    ASSERT_DOUBLE_EQ(3.0, SPointerCast<Constant>(div->lArg)->value);
    ASSERT_TRUE(isTypeOf<Variable>(div->rArg));
    ASSERT_STREQ("x", SPointerCast<Variable>(div->rArg)->name.c_str());
    
    ASSERT_TRUE(isTypeOf<Mult>(sum->rArg));
    PMult multR=SPointerCast<Mult>(sum->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(multR->lArg));
    ASSERT_DOUBLE_EQ(0.0, SPointerCast<Constant>(multR->lArg)->value);
    ASSERT_TRUE(isTypeOf<Ln>(multR->rArg));
    PLn ln=SPointerCast<Ln>(multR->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(ln->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(ln->arg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_ExponentiationOperationIsIncoplete_TraverseException) {
    PExpression exp = createPow(nullptr, createVariable("a"));
    
    Differentiator differentiator("a");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_SineFunction_ChainAndTrigonometricRulesApplied) {
    PSin exp = createSin(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Cos>(difExpTyped->rArg));
    PCos cos=SPointerCast<Cos>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(cos->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(cos->arg)->name.c_str());
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
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult negatedSine=SPointerCast<Mult>(difExpTyped->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(negatedSine->lArg));
    ASSERT_DOUBLE_EQ(-1, SPointerCast<Constant>(negatedSine->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Sin>(negatedSine->rArg));
    PSin sin=SPointerCast<Sin>(negatedSine->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(sin->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(sin->arg)->name.c_str());
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
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Sum>(difExpTyped->rArg));
    PSum tangentSum=SPointerCast<Sum>(difExpTyped->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(tangentSum->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(tangentSum->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Pow>(tangentSum->rArg));
    PPow pow=SPointerCast<Pow>(tangentSum->rArg);
    ASSERT_TRUE(isTypeOf<Tan>(pow->lArg));
    PTan tan=SPointerCast<Tan>(pow->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(tan->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(tan->arg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_DOUBLE_EQ(2.0, SPointerCast<Constant>(pow->rArg)->value);
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
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Mult>(difExpTyped->rArg));
    PMult negated=SPointerCast<Mult>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(negated->lArg));
    ASSERT_DOUBLE_EQ(-1.0, SPointerCast<Constant>(negated->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Sum>(negated->rArg));
    PSum cotangentSum=SPointerCast<Sum>(negated->rArg);
    
    ASSERT_TRUE(isTypeOf<Constant>(cotangentSum->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(cotangentSum->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Pow>(cotangentSum->rArg));
    PPow pow=SPointerCast<Pow>(cotangentSum->rArg);
    ASSERT_TRUE(isTypeOf<Ctan>(pow->lArg));
    PCtan ctan=SPointerCast<Ctan>(pow->lArg);
    ASSERT_TRUE(isTypeOf<Variable>(ctan->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(ctan->arg)->name.c_str());
    ASSERT_TRUE(isTypeOf<Constant>(pow->rArg));
    ASSERT_DOUBLE_EQ(2.0, SPointerCast<Constant>(pow->rArg)->value);
}

TEST_F(FX_Differentiator, visit_CotangentFunctionWithoutArgument_TraverseException) {
    PCtan exp = createCtan(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_NaturalLogarithmFunction_ChainAndLogarithmRulesApplied) {
    PLn exp = createLn(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(exp->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Div>(difExpTyped->rArg));
    PDiv div=SPointerCast<Div>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Constant>(div->lArg));
    ASSERT_DOUBLE_EQ(1.0, SPointerCast<Constant>(div->lArg)->value);
    ASSERT_TRUE(isTypeOf<Variable>(div->rArg));
    ASSERT_STREQ("x", SPointerCast<Variable>(div->rArg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_NaturalLogarithmFunctionOfComplexArg_ChainAndLogarithmRulesApplied) {
    PLn test = createLn(createSub(
            createConstant(4), 
            createMult(createConstant(2), createVariable("x"))
            ));
    // (0-((0*x)+(2*1)))*(1/(4-(2*x)))
    PMult expected = createMult(
            createSub(createConstant(0), createSum(
                createMult(createConstant(0), createVariable("x")),
                createMult(createConstant(2), createConstant(1))
            )),
            createDiv(createConstant(1), createSub(
                createConstant(4), 
                createMult(createConstant(2), createVariable("x"))
                )
            )
            );
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(test->traverse(differentiator));
    
    PExpression res = differentiator.getLastVisitResult();
    ASSERT_TRUE(equals(expected, res)) << to_string(expected) << " != " << to_string(res);
}

TEST_F(FX_Differentiator, visit_NaturalLogarithmWithoutArgument_TraverseException) {
    PLn exp = createLn(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, visit_ExponentFunction_ChainRulesApplied) {
    PExp expr = createExp(createVariable("x"));
    
    Differentiator differentiator("x");
    ASSERT_NO_THROW(expr->traverse(differentiator));
    
    PExpression difExp = differentiator.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Mult>(difExp));    
    PMult difExpTyped=SPointerCast<Mult>(difExp);
    
    ASSERT_TRUE(isTypeOf<Constant>(difExpTyped->lArg));
    ASSERT_DOUBLE_EQ(1, SPointerCast<Constant>(difExpTyped->lArg)->value);
    
    ASSERT_TRUE(isTypeOf<Exp>(difExpTyped->rArg));
    PExp exp=SPointerCast<Exp>(difExpTyped->rArg);
    ASSERT_TRUE(isTypeOf<Variable>(exp->arg));
    ASSERT_STREQ("x", SPointerCast<Variable>(exp->arg)->name.c_str());
}

TEST_F(FX_Differentiator, visit_ExponentWithoutArgument_TraverseException) {
    PExp exp = createExp(nullptr);
    
    Differentiator differentiator("x");
    ASSERT_THROW(exp->traverse(differentiator), TraverseException);
}

TEST_F(FX_Differentiator, differentiate_NullExpression_TraverseException) {
    PExpression nullExpr;
    ASSERT_THROW(differentiate(nullExpr, "x"), TraverseException);
}