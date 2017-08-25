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

Differentiator::Differentiator(string var) : variable(var) {
}

void Differentiator::visit(const shared_ptr<const Constant> expr) throw (TraverseException) {
    if (expr->value.empty()) {
        // inprobable situation
        THROW(TraverseException, "Constant is empty.", "N.A");
    }
    this->setLastVisitResult(make_shared<Constant>("0"));
}

void Differentiator::visit(const shared_ptr<const Variable> expr) throw (TraverseException) {
    if (expr->name.empty()) {
        // inprobable situation
        THROW(TraverseException, "No variable name is given.", "N.A");
    }
    
    if (expr->name == this->variable) {
        this->setLastVisitResult(make_shared<Constant>("1"));
        return;
    }
    this->setLastVisitResult(make_shared<Constant>("0"));
}

void Differentiator::visit(const shared_ptr<const Sum> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    shared_ptr<Sum> difSummation = make_shared<Sum>();

    expr->lArg->traverse(*this);
    shared_ptr<Expression> lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    shared_ptr<Expression> rArg = this->getLastVisitResult();

    difSummation->lArg = lArg;
    difSummation->rArg = rArg;

    this->setLastVisitResult(difSummation);
}

void Differentiator::visit(const shared_ptr<const Sub> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    shared_ptr<Sub> difSubtraction = make_shared<Sub>();

    expr->lArg->traverse(*this);
    shared_ptr<Expression> lArg = this->getLastVisitResult();
    expr->rArg->traverse(*this);
    shared_ptr<Expression> rArg = this->getLastVisitResult();

    difSubtraction->lArg = lArg;
    difSubtraction->rArg = rArg;

    this->setLastVisitResult(difSubtraction);
}

void Differentiator::visit(const shared_ptr<const Div> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    // Quotient rule
    shared_ptr<Div> dif = make_shared<Div>();
    
    shared_ptr<Sub> difDividend=make_shared<Sub>();
    
    shared_ptr<Mult> difDividendMLeft=make_shared<Mult>();
    expr->lArg->traverse(*this);
    difDividendMLeft->lArg=this->getLastVisitResult();
    difDividendMLeft->rArg=expr->rArg;
            
    shared_ptr<Mult> difDividendMRight=make_shared<Mult>();
    difDividendMRight->lArg=expr->lArg;
    expr->rArg->traverse(*this);
    difDividendMRight->rArg=this->getLastVisitResult();
    
    difDividend->lArg=difDividendMLeft;
    difDividend->rArg=difDividendMRight;
    dif->lArg=difDividend;
    
    
    shared_ptr<Pow> difDivisor=make_shared<Pow>();
    difDivisor->lArg=expr->rArg;
    difDivisor->rArg=make_shared<Constant>("2");
    
    dif->rArg=difDivisor;
    
    this->setLastVisitResult(dif);
}

void Differentiator::visit(const shared_ptr<const Mult> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Pow> expr) throw (TraverseException) {
    if (!expr->isComplete()) {
        THROW(TraverseException, "Expression is not consistent.", "LArg: " + to_string(expr->lArg) + "RArg:" + to_string(expr->rArg));
    }
    
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Sin>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Cos>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Tan>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Ctan>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Ln>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

void Differentiator::visit(const shared_ptr<const Exp>) throw (TraverseException) {
    /// @TODO s.a.
    /// @TODO NYI
    this->setLastVisitResult(make_shared<Constant>("NYI"));
}

shared_ptr<Expression> Differentiator::getLastVisitResult() const {
    return this->result;
}

void Differentiator::setLastVisitResult(shared_ptr<Expression> result) {
    this->result = result;
}

