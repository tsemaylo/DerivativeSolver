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

#include <ExpressionFactory.h>

#include "ExceptionThrower.h"
#include "SumConstantsRule.h"

inline std::vector<std::unique_ptr<OptimizationRule>> Optimizer::summationRules(PSum expr) const {
    std::vector<std::unique_ptr<OptimizationRule>> rules;
    
    rules.push_back(std::make_unique<SumConstantsRule>(expr));
    
    return rules;
}


void Optimizer::visit(const PConstConstant expr) throw (TraverseException) {
    if (expr->value.empty()) {
        THROW(TraverseException, "Constant is empty.", "N.A");
    }
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
    
    // left and right aruments are the same variable - return 2 product of this variable
    
    // both arguments have the structure like C*f then perform summation
    // for example 4sin(x)+sinx(x) or 2x+x
    // question of equality of expressions
    
    
    // trygonometric rule: (sin(x))^2+(cos(x)^2)
    // so far, optional
    
}

void Optimizer::visit(const PConstSub expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
}

void Optimizer::visit(const PConstDiv expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
}

void Optimizer::visit(const PConstMult expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
}

void Optimizer::visit(const PConstPow expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
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