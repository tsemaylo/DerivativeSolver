/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Differentiator.cpp
 *
 * @brief Implementation of the differentiation logic.
 *
 * @since 25.03.2016
 * @author agor
 */

#include <ExpressionFactory.h>
#include "ExceptionThrower.h"
#include "Differentiator.h"

Differentiator::Differentiator(string var) : variable(var) {
}

void Differentiator::visit(const PConstConstant ) throw (TraverseException) {
    this->setLastVisitResult(createConstant(0));
}

void Differentiator::visit(const PConstVariable expr) throw (TraverseException) {
    if (expr->name.empty()) {
        // inprobable situation
        THROW(TraverseException, "No variable name is given.", "N.A");
    }
    
    if (expr->name == this->variable) {
        this->setLastVisitResult(createConstant("1"));
        return;
    }
    this->setLastVisitResult(createConstant("0"));
}

void Differentiator::visit(const PConstSum expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }

    expr->lArg->traverse(*this);
    PExpression lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    PExpression rArg = this->getLastVisitResult();

    this->setLastVisitResult(createSum(lArg, rArg));
}

void Differentiator::visit(const PConstSub expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    PExpression rArg = this->getLastVisitResult();

    this->setLastVisitResult(createSub(lArg, rArg));
}

void Differentiator::visit(const PConstDiv expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    // Quotient rule

    expr->lArg->traverse(*this);
    PMult difDividendMLeft=createMult(this->getLastVisitResult(), expr->rArg);
    
    expr->rArg->traverse(*this);
    PMult difDividendMRight=createMult(expr->lArg, this->getLastVisitResult());
    
    PSub difDividend=createSub(difDividendMLeft, difDividendMRight);
    PPow difDivisor=createPow(expr->rArg, createConstant("2"));
    
    this->setLastVisitResult(createDiv(difDividend, difDivisor));
}

void Differentiator::visit(const PConstMult expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));

    }
    
    // f'g + fg'
    
    expr->lArg->traverse(*this);
    PMult leftSumTerm = createMult(this->getLastVisitResult(), expr->rArg);

    expr->rArg->traverse(*this);
    PMult rightSumTerm = createMult(expr->lArg, this->getLastVisitResult());
    
    this->setLastVisitResult(createSum(leftSumTerm, rightSumTerm));
}

void Differentiator::visit(const PConstPow expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    // applying generalized power rule
    // in form (f^g)' = (f^g)*(f'g/f + g'ln(f))
    
    // (f^g)
    PPow leftMultplier=createPow(expr->lArg, expr->rArg);
    
    // (f'g/f + g'ln(f))
    PSum rightMultplier=createSum();
    
    // f'g/f 
    expr->lArg->traverse(*this);
    rightMultplier->lArg = createMult(this->getLastVisitResult(), createDiv(expr->rArg, expr->lArg));
    // g'ln(f)
    expr->rArg->traverse(*this);
    rightMultplier->rArg = createMult(this->getLastVisitResult(), createLn(expr->lArg));
    
    this->setLastVisitResult(createMult(leftMultplier, rightMultplier));
}

void Differentiator::visit(const PConstSin expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }
    
    // the chain rule can be applied here
    // f(g(x))' = g' * f'(g)
    
    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(this->getLastVisitResult(), createCos(expr->arg)));
}

void Differentiator::visit(const PConstCos expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    // the chain rule is also applied here

    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(
            this->getLastVisitResult(),
            createMult(createConstant("-1"), createSin(expr->arg))
            )
            );
}

void Differentiator::visit(const PConstTan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    // the chain rule is also applied here

    // tan'(x) = 1 + (tan(x))^2
    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(
            this->getLastVisitResult(),
            createSum(
            createConstant("1"),
            createPow(createTan(expr->arg), createConstant("2"))
            )
            )
            );
}

void Differentiator::visit(const PConstCtan expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    // the chain rule is also applied here

    // ctan'(x) = -(1 + (ctan(x))^2)
    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(
            this->getLastVisitResult(),
            createMult(createConstant("-1"),
            createSum(
            createConstant("1"),
            createPow(createCtan(expr->arg), createConstant("2"))
            )
            )
            )
            );
}

void Differentiator::visit(const PConstLn expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    // the chain rule is also applied here
    
    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(
            this->getLastVisitResult(),
            createDiv(createConstant("1"), expr->arg)
            )
            );
}

void Differentiator::visit(const PConstExp expr) throw (TraverseException) {
        if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "Arg: " + to_string(expr->arg));
    }

    // the chain rule is also applied here

    expr->arg->traverse(*this);
    this->setLastVisitResult(createMult(
            this->getLastVisitResult(),
            createExp(expr->arg)
            )
            );
}

PExpression Differentiator::getLastVisitResult() const {
    return this->result;
}

void Differentiator::setLastVisitResult(PExpression result) {
    this->result = result;
}

