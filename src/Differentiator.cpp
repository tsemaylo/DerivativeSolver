/**
 * @file Differentiator.cpp
 *
 * @brief Implementation of the differentiation logic.
 *
 * @since 25.03.2016
 * @author agor
 */

#include "bootstrap.h"
#include "Differentiator.h"
#include "ExpressionFactory.h"

Differentiator::Differentiator(string var) : variable(var) {
}

void Differentiator::visit(const shared_ptr<const Constant> expr) throw (TraverseException) {
    if (expr->value.empty()) {
        // inprobable situation
        THROW(TraverseException, "Constant is empty.", "N.A");
    }
    this->setLastVisitResult(createConstant("0"));
}

void Differentiator::visit(const shared_ptr<const Variable> expr) throw (TraverseException) {
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

void Differentiator::visit(const shared_ptr<const Sum> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }

    expr->lArg->traverse(*this);
    PExpression lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    PExpression rArg = this->getLastVisitResult();

    this->setLastVisitResult(createSum(lArg, rArg));
}

void Differentiator::visit(const shared_ptr<const Sub> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    expr->lArg->traverse(*this);
    PExpression lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    PExpression rArg = this->getLastVisitResult();

    this->setLastVisitResult(createSub(lArg, rArg));
}

void Differentiator::visit(const shared_ptr<const Div> expr) throw (TraverseException) {
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

void Differentiator::visit(const shared_ptr<const Mult> expr) throw (TraverseException) {
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

void Differentiator::visit(const shared_ptr<const Pow> expr) throw (TraverseException) {
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

void Differentiator::visit(const shared_ptr<const Sin>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

void Differentiator::visit(const shared_ptr<const Cos>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

void Differentiator::visit(const shared_ptr<const Tan>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

void Differentiator::visit(const shared_ptr<const Ctan>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

void Differentiator::visit(const shared_ptr<const Ln>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

void Differentiator::visit(const shared_ptr<const Exp>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(createConstant("NYI"));
}

PExpression Differentiator::getLastVisitResult() const {
    return this->result;
}

void Differentiator::setLastVisitResult(PExpression result) {
    this->result = result;
}

