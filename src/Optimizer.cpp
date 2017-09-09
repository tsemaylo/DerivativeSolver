/**
 * @file Optimizer.cpp
 * 
 * Implementation of Optimizer.
 * 
 * @author agor
 * @since 09.09.2017
 */

#include "Optimizer.h"

#include <ExpressionFactory.h>
#include <vector>
#include <sstream>
#include <iomanip>
#include "ExceptionThrower.h"

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
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression optimizedLArg=this->getLastVisitResult();
    
    expr->rArg->traverse(*this);
    PExpression optimizedRArg=this->getLastVisitResult();
    
    // @TODO FIXME
    
    // some sketches to find out the proper design approch
    // 1. iterate throug through the list of rules
    // pros: adheres to OCP
    // cons: can be overdesign, the interface of these rule might be not consistent and pretty tightly coupled to with the Optimizer..
    // how much entities do we need to produce: 5 rule pro operation * 5 operations = At least 25 new classes..
//    for(auto rule : sumRules){
        // what is returt value of apply?
        // if, bool then how can we get a new Expression object if the new type of expression has to be substituted?
        // return an object? how can we determine if the rule is appliable?
        // 
//        if(rule.apply(expr)){
//            
//            break;
//        }
//    }
    
    // 2. code everything in straight-forward manner
    // pros: easy to implement, and the result will be quite coherent with Optimizer responsibility
    // cons: tonns of logic inside the optimizer.
    
    
    // constant and constand - perform summation and return constant
    if (isTypeOf<Constant>(optimizedLArg) && isTypeOf<Constant>(optimizedRArg)) {
        double lArgVal = 0.0;
        double rArgVal = 0.0;
        try {
            lArgVal = std::stod(SPointerCast<Constant>(optimizedLArg)->value);
            rArgVal = std::stod(SPointerCast<Constant>(optimizedRArg)->value);

            std::stringstream strStream;
            strStream << std::fixed << std::setprecision(2) << (lArgVal + rArgVal);
            PConstant result = createConstant(strStream.str());
            this->setLastVisitResult(result);
        }        catch (std::exception ex) {
            // re-throw an exception
            THROW(TraverseException, ex.what(), "N.A.");
        }
    } else {
        this->setLastVisitResult(createSum(optimizedLArg, optimizedRArg));
    }
    
    // right argument and 0 constant - return right argument
    
    // left argument and 0 constant - return left argument
    
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