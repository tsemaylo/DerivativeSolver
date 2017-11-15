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

#include <ExpressionFactory.h>

#include "ExceptionThrower.h"
#include "SumConstantsRule.h"
#include "SumWithNullArgumentRule.h"
#include "SumIdenticalExpressionsRule.h"
#include "MultConstantsRule.h"
#include "MultIdenticalExpressionsRule.h"

inline std::vector<std::unique_ptr<OptimizationRule>> Optimizer::summationRules(PSum expr) const {
    std::vector<std::unique_ptr<OptimizationRule>> rules;
    
    rules.push_back(std::make_unique<SumConstantsRule>(expr));
    rules.push_back(std::make_unique<SumWithNullArgumentRule>(expr));
    rules.push_back(std::make_unique<SumIdenticalExpressionsRule>(expr));
    
    return rules;
}

inline std::vector<std::unique_ptr<OptimizationRule>> Optimizer::multiplicationRules(PMult expr) const {
    std::vector<std::unique_ptr<OptimizationRule>> rules;
    
    rules.push_back(std::make_unique<MultConstantsRule>(expr));
    rules.push_back(std::make_unique<MultIdenticalExpressionsRule>(expr));
    
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

inline PExpression Optimizer::negateExpression(PExpression expr) const throw(TraverseException){
    if(isTypeOf<Mult>(expr)){
        PMult typedExpr=SPointerCast<Mult>(expr);
        
        auto negateConstant = [](PConstant c) throw(TraverseException) -> PConstant {
            return createConstant(SPointerCast<Constant>(c)->value * -1.0);
        };
        
        if(isTypeOf<Constant>(typedExpr->lArg)){
            return createMult(negateConstant(SPointerCast<Constant>(typedExpr->lArg)), typedExpr->rArg);
        }else if(isTypeOf<Constant>(typedExpr->rArg)){
            return createMult(negateConstant(SPointerCast<Constant>(typedExpr->rArg)),typedExpr->lArg);
        }else{
            return createMult(createConstant(-1), expr);
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
    
    PSum sumWithOptimizedArgs = createSum(optimizedLArg, this->negateExpression(optimizedRArg));
    
    for (auto &rule : summationRules(sumWithOptimizedArgs)){
        if (rule->apply()) {
            this->setLastVisitResult(rule->getOptimizedExpression());
            return;
        }
    }
    this->setLastVisitResult(sumWithOptimizedArgs);
    return;
}

void Optimizer::visit(const PConstDiv expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    // 0/Expression = 0
    
    // Expression/1 = Expression
    
    // (Expression1) / (Expression2) == Expression1 * 1/Expression2  - 
    //      constants on the right side must be precalculated if we want to 
    //      employ multiplication rules
    
    this->setLastVisitResult(createDiv(expr->lArg, expr->rArg));
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
    
    // @TODO A*Expression^M * B*Expression^N =  AB*Expression^(M+N)
    // with subcase: A/(Expression^N) * (Expression^M)/B = (A/B) * Expression^(M-N)
}

void Optimizer::visit(const PConstPow expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    // A^B -> calculate results
    
    // Expression ^ 0 = 1
    
    // Expression ^ 1 = Expression
    
    this->setLastVisitResult(createPow(expr->lArg, expr->rArg));
}

void Optimizer::visit(const PConstSin expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

void Optimizer::visit(const PConstCos expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

void Optimizer::visit(const PConstTan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

void Optimizer::visit(const PConstCtan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

void Optimizer::visit(const PConstLn expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

void Optimizer::visit(const PConstExp expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
}

PExpression Optimizer::getLastVisitResult() const {
    return this->result;
}

void Optimizer::setLastVisitResult(PExpression result) {
    this->result = result;
}