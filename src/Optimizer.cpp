/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Optimizer.cpp
 * 
 * Implementation of Optimizer.
 * 
 * @author agor
 * @since 09.09.2017
 */

#include "Optimizer.h"

#include <memory>
#include <ios>
#include <iomanip>
#include <sstream>
#include <cmath>

#include <ExpressionFactory.h>
#include <Expression.h>

#include "ExceptionThrower.h"
#include "SumConstantsRule.h"
#include "SumWithNullArgumentRule.h"
#include "SumIdenticalExpressionsRule.h"
#include "MultConstantsRule.h"
#include "MultIdenticalExpressionsRule.h"
#include "PowConstantRule.h"
#include "PowOfPowRule.h"
#include "OptimizationRule.tpp"
#include "FunctionEvaluateRule.tpp"
#include "LnOfExpRule.h"

/**
 * Initialize the vector of optimization rules for summation expression.
 * 
 * @param expr The Summation expression.
 * @return Vector consisting of unique pointers to OptimizationRule's.
 */
inline std::vector<std::unique_ptr<OptimizationRule<PSum>>> summationRules(PSum expr) {
    std::vector<std::unique_ptr<OptimizationRule<PSum>>> rules;
    
    rules.push_back(std::make_unique<SumConstantsRule>(expr));
    rules.push_back(std::make_unique<SumWithNullArgumentRule>(expr));
    rules.push_back(std::make_unique<SumIdenticalExpressionsRule>(expr));
    
    return rules;
}

/**
 * Initialize the vector of optimization rules for multiplication expression.
 * 
 * @param expr The Mult expression.
 * @return Vector consisting of unique pointers to OptimizationRule's.
 */
inline std::vector<std::unique_ptr<OptimizationRule<PMult>>> multiplicationRules(PMult expr) {
    std::vector<std::unique_ptr<OptimizationRule<PMult>>> rules;
    
    rules.push_back(std::make_unique<MultConstantsRule>(expr));
    rules.push_back(std::make_unique<MultIdenticalExpressionsRule>(expr));
    
    return rules;
}

/**
 * Initialize the vector of optimization rules for exponentiation expression.
 * 
 * @param expr The Pow expression.
 * @return Vector consisting of unique pointers to OptimizationRule's.
 */
inline std::vector<std::unique_ptr<OptimizationRule<PPow>>> exponentiationRules(PPow expr) {
    std::vector<std::unique_ptr<OptimizationRule<PPow>>> rules;
    
    rules.push_back(std::make_unique<PowConstantRule>(expr));
    rules.push_back(std::make_unique<PowOfPowRule>(expr));
    
    return rules;
}

void Optimizer::visit(const PConstConstant expr) throw (TraverseException) {
    // Not applicable
    this->setLastVisitResult(createConstant(expr->value));
}

void Optimizer::visit(const PConstVariable expr) throw (TraverseException) {
    if (expr->name.empty()) {
        THROW(TraverseException, "No variable name is given.", "N.A");
    }
    // Not applicable
    this->setLastVisitResult(createVariable(expr->name));
}

void Optimizer::visit(const PConstSum expr) throw (TraverseException) {
    // @TODO FIXME copypaste-copypaste
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    PSum sumWithOptimizedArgs =createSum(optimizedLArg, optimizedRArg);
    for (auto &rule : summationRules(sumWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    this->setLastVisitResult(sumWithOptimizedArgs);
    return;
    
    // @TODO think about trygonometric rules: (sin(x))^2+(cos(x)^2)
}

/**
 * Get the negative counterpart of given expression.
 * 
 * For instance: for negateExpression(a) = -a
 * If the expr is Variable or any function the Mult with 
 * "-1" as left argument will be returned.
 * 
 * @param expr The expression to be negated.
 * 
 * @return Negative expression.
 */
inline PExpression negateExpression(PExpression expr) throw(TraverseException){
    if(isTypeOf<Mult>(expr)){
        PMult typedExpr=SPointerCast<Mult>(expr);
        
        auto negateConstant = [](PConstant c) throw(TraverseException) -> PConstant {
            return createConstant(c->value * -1.0);
        };
        
        if(isTypeOf<Constant>(typedExpr->lArg)){
            return createMult(negateConstant(SPointerCast<Constant>(typedExpr->lArg)), typedExpr->rArg);
        }else if(isTypeOf<Constant>(typedExpr->rArg)){
            return createMult(negateConstant(SPointerCast<Constant>(typedExpr->rArg)),typedExpr->lArg);
        }else{
            return createMult(createConstant(-1.0), expr);
        }
    }else{
        return createMult(createConstant(-1), expr);
    }
    
    // @TODO what about Div?
}

void Optimizer::visit(const PConstSub expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    // reprsent as summation and apply summation rules
    
    PSum sumWithOptimizedArgs = createSum(optimizedLArg, negateExpression(optimizedRArg));
    
    for (auto &rule : summationRules(sumWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    this->setLastVisitResult(createSub(optimizedLArg, optimizedRArg));
    return;
}

/**
 * Obtain the inverted expression. For example: invertDenominator(x) = 1/x
 * 
 * @param expr Expression to invert
 * @return 
 */
inline PExpression invertDenominator(PExpression expr) throw(TraverseException){
    if(isTypeOf<Pow>(expr)){
        // x^n => x^-n
        PPow typedExpr=SPointerCast<Pow>(expr);
        if(isTypeOf<Constant>(typedExpr->rArg)){
            return createPow(typedExpr->lArg, createConstant(SPointerCast<Constant>(typedExpr->rArg)->value*-1.0));
        }
        return createPow(typedExpr->lArg, createMult(typedExpr->rArg, createConstant(-1.0)));
    }
    if(isTypeOf<Div>(expr)){
        // n/x => 1/n * x
        PDiv typedExpr=SPointerCast<Div>(expr);
        if(isTypeOf<Constant>(typedExpr->lArg)){
            return createMult(createConstant(1.0/(SPointerCast<Constant>(typedExpr->lArg))->value), typedExpr->rArg);
        }
        // x/y => y/x
        return createMult(typedExpr->lArg, typedExpr->rArg);
    }
    if(isTypeOf<Constant>(expr)){
        // n => 1/n 
        PConstant typedExpr=SPointerCast<Constant>(expr);
        if(typedExpr->value!=0.0){
            return createConstant(1.0/(typedExpr->value));
        }
    }
    // default rule
    return createPow(expr, createConstant(-1.0));
}

void Optimizer::visit(const PConstDiv expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    // reprsent as product and apply multiplicationrules
    
    PMult multWithOptimizedArgs = createMult(optimizedLArg, invertDenominator(optimizedRArg));
    
    for (auto &rule : multiplicationRules(multWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    this->setLastVisitResult(createDiv(optimizedLArg, optimizedRArg));
    return;
}

void Optimizer::visit(const PConstMult expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    PMult multWithOptimizedArgs =createMult(optimizedLArg, optimizedRArg);
    for (auto &rule : multiplicationRules(multWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    this->setLastVisitResult(multWithOptimizedArgs);
    return;
}

void Optimizer::visit(const PConstPow expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    PPow powWithOptimizedArgs =createPow(optimizedLArg, optimizedRArg);
    for (auto &rule : exponentiationRules(powWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    
    this->setLastVisitResult(powWithOptimizedArgs);
    return;
}

void Optimizer::visit(const PConstSin expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PSin sinWithOptimizedArgs =createSin(optimizedArg);
    
    FunctionEvaluateRule<Sin> rule(sinWithOptimizedArgs, [](double v) -> double{ return std::sin(v); });
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(sinWithOptimizedArgs);
}

void Optimizer::visit(const PConstCos expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PCos cosWithOptimizedArgs =createCos(optimizedArg);
    
    FunctionEvaluateRule<Cos> rule(cosWithOptimizedArgs, [](double v) -> double{ return std::cos(v); });
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(cosWithOptimizedArgs);
}

void Optimizer::visit(const PConstTan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PTan tanWithOptimizedArgs =createTan(optimizedArg);
    
    FunctionEvaluateRule<Tan> rule(tanWithOptimizedArgs, [optimizedArg](double v) -> double{ 
        double pi=3.14159265358979323846; 
        double n = v/(pi/2.0);
        double nint=std::round(n);
        if(equals(createConstant(n), createConstant(nint))){ 
            // tangent is not defined here
            THROW(TraverseException, "Argumenmt of tangent is not correct, infinite result is expected here!", "tan("+to_string(optimizedArg)+")");
        }
        return std::tan(v); 
    });
    
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(tanWithOptimizedArgs);
}

void Optimizer::visit(const PConstCtan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PCtan ctanWithOptimizedArgs =createCtan(optimizedArg);
    
    FunctionEvaluateRule<Ctan> rule(ctanWithOptimizedArgs, [optimizedArg](double v) -> double{ 
        double pi=3.14159265358979323846; 
        double n = v/pi;
        double nint=std::round(n);
        if(equals(createConstant(n), createConstant(nint))){ 
            // cotangent is not defined here
            THROW(TraverseException, "Argumenmt of cotangent is not correct, infinite result is expected here!", "ctan("+to_string(optimizedArg)+")");
        }
        return std::cos(v)/std::sin(v); 
    });
    
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(ctanWithOptimizedArgs);
}

void Optimizer::visit(const PConstLn expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PLn lnWithOptimizedArgs =createLn(optimizedArg);
    
    FunctionEvaluateRule<Ln> ruleEval(lnWithOptimizedArgs, [optimizedArg](double v) -> double{ 
        if(v <= 0.0){ 
            // cotangent is not defined here
            THROW(TraverseException, "Argumenmt of natural logarithm cant be <= 0, infinite result is expected here!", "ln("+to_string(optimizedArg)+")");
        }
        return std::log(v); 
    });
    if(ruleEval.apply()){
        this->setLastVisitResult(ruleEval.getOptimizedExpression());
        return;
    }
    
    LnOfExpRule ruleLnExp(lnWithOptimizedArgs);
    if(ruleLnExp.apply()){
        this->setLastVisitResult(ruleLnExp.getOptimizedExpression());
        return;
    }

    this->setLastVisitResult(lnWithOptimizedArgs);
    
    // the same a for all functions + ln(exp(x))=x
}

void Optimizer::visit(const PConstExp expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    PExp expWithOptimizedArgs =createExp(optimizedArg);
    
    FunctionEvaluateRule<Exp> rule(expWithOptimizedArgs, [](double v) -> double{ 
        return std::exp(v); 
    });
    
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(expWithOptimizedArgs);
}

PExpression Optimizer::getLastVisitResult() const {
    return this->result;
}

void Optimizer::setLastVisitResult(PExpression result) {
    this->result = result;
}

PExpression optimize(PExpression expr) throw (TraverseException){
    bool isDone=false;
    const auto attemtLimit=10; 
    auto attemptN=0;
    
    // try to otimize the expression severaltime until the optimization result 
    // will not differ
    PExpression previousExpression=expr;
    while(!isDone && attemptN < attemtLimit){
        Optimizer optimizer;
        expr->traverse(optimizer);
        PExpression optimizedExpr=optimizer->getLastVisitResult();
        isDone = equals(optimizedExpr, previousExpression);
        
        previousExpression=optimizedExpr;
        attemptN++;
    }
}