/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file OptimizerTest.cpp
 * 
 * Tests for Optimizer.
 *
 * @since 09.09.2017
 * @author agor
 */

#include <gtest/gtest.h>

#include "Optimizer.h"
#include "Constant.h"
#include "Sum.h"
#include "Doubles.h"
#include "ExpressionFactory.h"

class FX_Optimizer : public testing::Test {
protected:

    virtual void SetUp() {
    }

    virtual void TearDown() {
    }
};

TEST_F(FX_Optimizer, visit_SumOfTwoConstants_Constant) {
    PSum exp = createSum(createConstant(2.0), createConstant(3.0));
    
    Optimizer optimizer;
    ASSERT_NO_THROW(exp->traverse(optimizer));
    
    PExpression optExp=optimizer.getLastVisitResult();
    ASSERT_TRUE(isTypeOf<Constant>(optExp));
    
    PConstant optExpTyped = SPointerCast<Constant>(optExp);
    
    ASSERT_DOUBLE_EQ(5.0, optExpTyped->value);
}

TEST_F(FX_Optimizer, visit_Subtraction_ApplicableAndSuccessfull) {
    std::vector<PSub> tests;
    std::vector<PExpression> expResults;
    
    tests.push_back(createSub(createMult(createConstant(5.0), createVariable("x")), createMult(createConstant(3.0), createVariable("x"))));
    expResults.push_back(createMult(createConstant(2.0), createVariable("x")));
    
    tests.push_back(createSub(createMult(createConstant(3.0), createVariable("x")), createMult(createConstant(5.0), createVariable("x"))));
    expResults.push_back(createMult(createConstant(-2.0), createVariable("x")));
    
    tests.push_back(createSub(createMult(createConstant(3.0), createVariable("x")), createVariable("x")));
    expResults.push_back(createMult(createConstant(2.0), createVariable("x")));
    
    tests.push_back(createSub(createVariable("x"), createMult(createVariable("x"), createConstant(3.0))));
    expResults.push_back(createMult(createConstant(-2.0), createVariable("x")));
    
    tests.push_back(createSub(createVariable("x"), createMult(createConstant(3.0), createVariable("x"))));
    expResults.push_back(createMult(createConstant(-2.0), createVariable("x")));
    
    tests.push_back(createSub(createVariable("x"), createVariable("x")));
    expResults.push_back(createMult(createConstant(0.0), createVariable("x")));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        Optimizer optimizer;
        EXPECT_NO_THROW(tests[testId]->traverse(optimizer)) << "Test ID=" << testId << " threw an exception!";
        PExpression actResult=optimizer.getLastVisitResult();
        string expected=to_string(expResults[testId]);
        string actual=to_string(actResult);
        EXPECT_TRUE(equals(expResults[testId], actResult)) << 
                "Result does not match for test ID=" << testId << "! (" 
                << expected << " != " << actual;
    }
}

TEST_F(FX_Optimizer, visit_Subtraction_NotAppliable) {
    std::vector<PSub> tests;
    
    tests.push_back(createSub(createMult(createConstant(5.0), createVariable("x")), createMult(createVariable("y"), createVariable("x"))));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        Optimizer optimizer;
        EXPECT_NO_THROW(tests[testId]->traverse(optimizer)) << "Test ID=" << testId << " threw an exception!";
        PExpression actResult=optimizer.getLastVisitResult();
        string expected=to_string(tests[testId]);
        string actual=to_string(actResult);
        EXPECT_TRUE(equals(tests[testId], actResult)) << 
                "Result does not match for test ID=" << testId << "! (" 
                << expected << " != " << actual;
    }
}

TEST_F(FX_Optimizer, visit_Division_ApplicableAndSuccessfull) {
    std::vector<PDiv> tests;
    std::vector<PExpression> expResults;
    
    // x/1
    tests.push_back(createDiv(createVariable("x"), createConstant(1)));
    expResults.push_back(createVariable("x"));
    
    // 0/sin(x)
    tests.push_back(createDiv(createConstant(0), createSin(createVariable("x"))));
    expResults.push_back(createConstant(0));
    
    // x/x => 1*x^(1+-1)
    tests.push_back(createDiv(createVariable("x"), createVariable("x")));
    expResults.push_back(createMult(
        createConstant(1), 
        createPow(createVariable("x"), createSum(createConstant(1), createConstant(-1)))
    ));
    
    // x^2/x => 1*x^(2+-1)
    tests.push_back(createDiv(createPow(createVariable("x"),createConstant(2)), createVariable("x")));
    expResults.push_back(createMult(
        createConstant(1), 
        createPow(createVariable("x"), createSum(createConstant(2), createConstant(-1)))
    ));
    
    // x/(x^2) => 1*x^(1+-2)
    tests.push_back(createDiv(createVariable("x"), createPow(createVariable("x"),createConstant(2))));
    expResults.push_back(createMult(
        createConstant(1), 
        createPow(createVariable("x"), createSum(createConstant(1), createConstant(-2)))
    ));
    
    // (3x)/(3/x) => 1*x^(1+1)
    tests.push_back(createDiv(
        createMult(createConstant(3), createVariable("x")),
        createDiv(createConstant(3), createVariable("x"))
    ));
    expResults.push_back(createMult(
        createConstant(1), 
        createPow(createVariable("x"), createSum(createConstant(1), createConstant(1)))
    ));
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        Optimizer optimizer;
        EXPECT_NO_THROW(tests[testId]->traverse(optimizer)) << "Test ID=" << testId << " threw an exception!";
        PExpression actResult=optimizer.getLastVisitResult();
        string expected=to_string(expResults[testId]);
        string actual=to_string(actResult);
        EXPECT_TRUE(equals(expResults[testId], actResult)) << 
                "Result does not match for test ID=" << testId << "! (" 
                << expected << " != " << actual;
    }
}

TEST_F(FX_Optimizer, optimize_SimpleOptimizations_Successfull) {
    std::vector<PExpression> tests;
    std::vector<PExpression> expResults;
    
    // x/1
    tests.push_back(createDiv(createVariable("x"), createConstant(1)));
    expResults.push_back(createVariable("x"));
    
    // cos(1-(x*x)/((x^0.5)^4)) + (1/x)*x^2 - ln(exp(x)) = 1 
    {
        PExpression term1=createCos(
            createSub(
                createConstant(1.0),
                createDiv(
                    createMult(createVariable("x"), createVariable("x")),
                    createPow(createPow(createVariable("x"),createConstant(0.5)),createConstant(4.))
                )
            )
        );
        PExpression term2=createMult(
                createDiv(createConstant(1.0), createVariable("x")),
                createPow(createVariable("x"), createConstant(2.0))
        );
        PExpression term3=createLn(createExp(createVariable("x")));

        tests.push_back(createSum(term1, createSub(term2, term3)));
        expResults.push_back(createConstant(1.0));
    }
    
    // (tan(ctan(pi/2)) + x^5) / (3x-exp(0)*2x) = x^4
    {
        
        
        PExpression term1= createSum(
            createTan(createCtan(createConstant(PI/2))),
            createPow(createVariable("x"), createConstant(5.0))
        );
        PExpression term2=createSub(
            createMult(createConstant(3), createVariable("x")),
            createMult(createConstant(2), createMult(
                createExp(createConstant(0)),
                createVariable("x")
                )
            )
        );
            
        tests.push_back(createDiv(term1, term2));
        expResults.push_back(createPow(createVariable("x"), createConstant(4.0)));
    }
    
    // sin(-pi/2 * cos(2pi))
    {   
        PExpression expr= createSin(createMult(
            createMult(
                createConstant(-1), 
                createDiv(createConstant(PI), createConstant(2))
            ), 
            createCos(createMult(createConstant(2), createConstant(PI)))
        ));
            
        tests.push_back(expr);
        expResults.push_back(createConstant(-1));
    }
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        PExpression actResult;
        EXPECT_NO_THROW(actResult=optimize(tests[testId])) << "Test ID=" << testId << " threw an exception!";
        string expected=to_string(expResults[testId]);
        string actual=to_string(actResult);
        EXPECT_TRUE(equals(expResults[testId], actResult)) << 
                "Result does not match for test ID=" << testId << "! (" 
                << expected << " != " << actual;
    }
}

TEST_F(FX_Optimizer, optimize_ExceptionalCases_TraverseException) {
    std::vector<PExpression> tests;
    
    // incomplete expressions
    tests.push_back(createSum());  // 00
    tests.push_back(createSub());  // 01
    tests.push_back(createMult()); // 02
    tests.push_back(createDiv());  // 03
    tests.push_back(createPow());  // 04
    tests.push_back(createSin());  // 05
    tests.push_back(createCos());  // 06
    tests.push_back(createTan());  // 07
    tests.push_back(createCtan()); // 08
    tests.push_back(createLn());   // 09
    tests.push_back(createExp());  // 10
    
    // illegal arguments
    tests.push_back(createDiv(createConstant(1), createConstant(0))); // 11
    tests.push_back(createTan(createConstant(PI/2))); //12
    tests.push_back(createCtan(createConstant(2*PI))); //13
    
    for(unsigned int testId=0; testId < tests.size(); testId++){
        EXPECT_THROW(optimize(tests[testId]), TraverseException) << "Test ID=" << testId << " did not throw an exception!";
    }
}