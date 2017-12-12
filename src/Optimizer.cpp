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

#include "Doubles.h"
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
    
    // @TODO think about trygonometric rules: (sin(x))^2+(cos(x)^2)
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


template <typename PCT, typename PT>
PT Optimizer::optimizeArgumentsDiadic(const PCT expr, std::function<PT (PExpression, PExpression)> factory) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    return factory(optimizedLArg, optimizedRArg);
}

template <typename PCT, typename PT>
PT Optimizer::optimizeArgumentMonadic(const PCT expr, std::function<PT (PExpression)> factory) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    expr->arg->traverse(*this);
    PExpression optimizedArg=this->getLastVisitResult();
    
    return factory(optimizedArg);
}

/**
 * Apply rules from the collection for the expression of type PT (rule must me suitable for type PT).
 * 
 * @param rules Vectror of OptimizationRule's. 
 * @param ifApplied Lambda which will be executed if at least one rule has been applied.
 * @param ifNotApplied Lambda which will be executed if no rule has been applied.
 */
template <typename PT>
void applyCollectionOfRules(std::vector<std::unique_ptr<OptimizationRule<PT>>> rules,
        std::function<void(PExpression)> ifApplied, std::function<void()> ifNotApplied) {
    for (auto &rule : rules){
        if (rule->apply()) {
            ifApplied(rule->getOptimizedExpression());
            return;
        }
    }
    ifNotApplied();
}

void Optimizer::visit(const PConstSum expr) throw (TraverseException) {
    PSum sumWithOptimizedArgs = optimizeArgumentsDiadic<PConstSum, PSum>(expr, [](PExpression lArg, PExpression rArg) -> PSum {
        return createSum(lArg, rArg);
    });
    
    applyCollectionOfRules<PSum>(summationRules(sumWithOptimizedArgs), [this](PExpression optimizedExpression){
        this->setLastVisitResult(optimizedExpression);
    }, 
    [this, &sumWithOptimizedArgs](){
        this->setLastVisitResult(sumWithOptimizedArgs);
    }
    );
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
    PSub subWithOptimizedArgs = optimizeArgumentsDiadic<PConstSub, PSub>(expr, [](PExpression lArg, PExpression rArg) -> PSub {
        return createSub(lArg, rArg);
    });
    
    // reprsent as summation and apply summation rules
    negateExpression(subWithOptimizedArgs->rArg)->traverse(*this);
    PExpression optimizedNegatedRArg=this->getLastVisitResult();
    PSum sumWithOptimizedArgs = createSum(subWithOptimizedArgs->lArg, optimizedNegatedRArg);
    
    applyCollectionOfRules<PSum>(summationRules(sumWithOptimizedArgs), [this](PExpression optimizedExpression){
        this->setLastVisitResult(optimizedExpression);
    }, 
    [this, &subWithOptimizedArgs](){
        this->setLastVisitResult(subWithOptimizedArgs);
    });
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
    if(isTypeOf<Mult>(expr)) {
	// n*x => 1/n * x^-1
	PMult typedExpr=SPointerCast<Mult>(expr);
	if(isTypeOf<Constant>(typedExpr->lArg)){
	    return createMult(
		    createDiv(createConstant(1.0), typedExpr->lArg),
		    createPow(typedExpr->rArg, createConstant(-1.0))
		    );
	}else if(isTypeOf<Constant>(typedExpr->rArg)){
	    return createMult(
		    createDiv(createConstant(1.0), typedExpr->rArg),
		    createPow(typedExpr->lArg, createConstant(-1.0))
		    );
	}
    }
    if(isTypeOf<Constant>(expr)){
        // n => 1/n 
        PConstant typedExpr=SPointerCast<Constant>(expr);
        if(equal(typedExpr->value, 0.0)){
            THROW(TraverseException, "Division by zero.", to_string(expr));
        }
        return createConstant(1.0/(typedExpr->value));
    }
    // default rule
    return createPow(expr, createConstant(-1.0));
}

void Optimizer::visit(const PConstDiv expr) throw (TraverseException) {
    PDiv divWithOptimizedArgs = optimizeArgumentsDiadic<PConstDiv, PDiv>(expr, [](PExpression lArg, PExpression rArg) -> PDiv {
        return createDiv(lArg, rArg);
    });
    
    // reprsent as product and apply multiplicationrules
    invertDenominator(divWithOptimizedArgs->rArg)->traverse(*this);
    PExpression optimizedInvertedRArg=this->getLastVisitResult();
    PMult multWithOptimizedArgs = createMult(divWithOptimizedArgs->lArg, optimizedInvertedRArg);
    
    applyCollectionOfRules<PMult>(multiplicationRules(multWithOptimizedArgs), [this](PExpression optimizedExpression){
        this->setLastVisitResult(optimizedExpression);
    }, 
    [this, &divWithOptimizedArgs](){
        this->setLastVisitResult(divWithOptimizedArgs);
    });
}

void Optimizer::visit(const PConstMult expr) throw (TraverseException) {
    PMult multWithOptimizedArgs = optimizeArgumentsDiadic<PConstMult, PMult>(expr, [](PExpression lArg, PExpression rArg) -> PMult {
        return createMult(lArg, rArg);
    });
    
    applyCollectionOfRules<PMult>(multiplicationRules(multWithOptimizedArgs), [this](PExpression optimizedExpression){
        this->setLastVisitResult(optimizedExpression);
    }, 
    [this, &multWithOptimizedArgs](){
        this->setLastVisitResult(multWithOptimizedArgs);
    });
}

void Optimizer::visit(const PConstPow expr) throw (TraverseException) {
    PPow powWithOptimizedArgs =optimizeArgumentsDiadic<PConstPow, PPow>(expr, [](PExpression lArg, PExpression rArg) -> PPow {
        return createPow(lArg, rArg);
    });
    
    applyCollectionOfRules<PPow>(exponentiationRules(powWithOptimizedArgs), [this](PExpression optimizedExpression){
        this->setLastVisitResult(optimizedExpression);
    }, 
    [this, &powWithOptimizedArgs](){
        this->setLastVisitResult(powWithOptimizedArgs);
    });
}

void Optimizer::visit(const PConstSin expr) throw (TraverseException) {
    PSin sinWithOptimizedArgs = optimizeArgumentMonadic<PConstSin, PSin>(expr, [](PExpression arg) -> PSin {
        return createSin(arg);
    });
    
    FunctionEvaluateRule<Sin> rule(sinWithOptimizedArgs, [](double v) -> double{ return std::sin(v); });
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(sinWithOptimizedArgs);
}

void Optimizer::visit(const PConstCos expr) throw (TraverseException) {
    PCos cosWithOptimizedArgs =optimizeArgumentMonadic<PConstCos, PCos>(expr, [](PExpression arg) -> PCos {
        return createCos(arg);
    });
    
    FunctionEvaluateRule<Cos> rule(cosWithOptimizedArgs, [](double v) -> double{ return std::cos(v); });
    if(rule.apply()){
        this->setLastVisitResult(rule.getOptimizedExpression());
        return;
    }
    
    this->setLastVisitResult(cosWithOptimizedArgs);
}

void Optimizer::visit(const PConstTan expr) throw (TraverseException) {
    PTan tanWithOptimizedArgs = optimizeArgumentMonadic<PConstTan, PTan>(expr, [](PExpression arg) -> PTan {
        return createTan(arg);
    });
    
    FunctionEvaluateRule<Tan> rule(tanWithOptimizedArgs, [&tanWithOptimizedArgs](double v) -> double{ 
        double n = ((2*v)+PI)/(2*PI);
        double nint = std::round(n);
        if(equal(n, nint)){ 
            // tangent is not defined here
            THROW(TraverseException, "Argumenmt of tangent is not correct, infinite result is expected here!", to_string(tanWithOptimizedArgs));
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
    PCtan ctanWithOptimizedArgs = optimizeArgumentMonadic<PConstCtan, PCtan>(expr, [](PExpression arg) -> PCtan {
        return createCtan(arg);
    });
    
    FunctionEvaluateRule<Ctan> rule(ctanWithOptimizedArgs, [&ctanWithOptimizedArgs](double v) -> double{ 
        double n = v/PI;
        double nint=std::round(n);
        if(equal(n, nint)){ 
            // cotangent is not defined here
            THROW(TraverseException, "Argumenmt of cotangent is not correct, infinite result is expected here!", to_string(ctanWithOptimizedArgs));
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
    PLn lnWithOptimizedArgs = optimizeArgumentMonadic<PConstLn, PLn>(expr, [](PExpression arg) -> PLn {
        return createLn(arg);
    });
    
    FunctionEvaluateRule<Ln> ruleEval(lnWithOptimizedArgs, [&lnWithOptimizedArgs](double v) -> double{ 
        if(v <= 0.0){ 
            // cotangent is not defined here
            THROW(TraverseException, "Argumenmt of natural logarithm cant be <= 0, infinite result is expected here!", to_string(lnWithOptimizedArgs));
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
}

void Optimizer::visit(const PConstExp expr) throw (TraverseException) {
    PExp expWithOptimizedArgs = optimizeArgumentMonadic<PConstExp, PExp>(expr, [](PExpression arg) -> PExp {
        return createExp(arg);
    });
    
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
    if(expr==nullptr){
        THROW(TraverseException, "Not possible to optimize the NULL expressions.", "N.A.");
    }
    
    bool isDone=false;
    const auto attemtLimit=20; 
    auto attemptN=0;
    
    // try to otimize the expression severaltime until the optimization result 
    // will not differ
    PExpression previousExpression=expr;
    while(!isDone || attemptN < attemtLimit){
        Optimizer optimizer;
        previousExpression->traverse(optimizer);
        PExpression optimizedExpr=optimizer.getLastVisitResult();
        isDone = equals(optimizedExpr, previousExpression);
        
        previousExpression=optimizedExpr;
        attemptN++;
    }
    
    return previousExpression;
}