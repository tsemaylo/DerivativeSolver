/**
 * @file Comparator.cpp
 * 
 * Implementation of Comparator class. 
 * @author agor
 * @since 09.10.2017
 */

#include "Comparator.h"

Comparator::Comparator(PExpression expr) : exprBeingCompared(expr) {

}

void Comparator::visit(const PConstConstant expr) throw (TraverseException) {
    if(isTypeOf<Constant>(this->exprBeingCompared)){
        this->result = SPointerCast<Constant>(this->exprBeingCompared)->value == expr->value;
        return;
    }
    this->result=false;
}

void Comparator::visit(const PConstVariable expr) throw (TraverseException) {
    if(isTypeOf<Variable>(this->exprBeingCompared)){
        this->result = SPointerCast<Variable>(this->exprBeingCompared)->name == expr->name;
        return;
    }
    this->result=false;
}

void Comparator::visit(const PConstSum expr) throw (TraverseException) {
    if(isTypeOf<Sum>(this->exprBeingCompared)){
        PSum sumBeingComp=SPointerCast<Sum>(this->exprBeingCompared);
        Comparator cmpL(sumBeingComp->lArg);
        Comparator cmpR(sumBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->lArg->traverse(cmpR);
        bool rl=cmpL.areEqual();
        
        expr->rArg->traverse(cmpL);
        bool lr=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpL.areEqual();
        
        this->result = (ll && rr) || (lr && rl);
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstSub expr) throw (TraverseException) {
    if(isTypeOf<Sub>(this->exprBeingCompared)){
        PSub subBeingComp=SPointerCast<Sub>(this->exprBeingCompared);
        Comparator cmpL(subBeingComp->lArg);
        Comparator cmpR(subBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpL.areEqual();
        
        this->result = ll && rr;
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstMult expr) throw (TraverseException) {
    if(isTypeOf<Mult>(this->exprBeingCompared)){
        PMult multBeingComp=SPointerCast<Mult>(this->exprBeingCompared);
        Comparator cmpL(multBeingComp->lArg);
        Comparator cmpR(multBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->lArg->traverse(cmpR);
        bool rl=cmpL.areEqual();
        
        expr->rArg->traverse(cmpL);
        bool lr=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpL.areEqual();
        
        this->result = (ll && rr) || (lr && rl);
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstDiv expr) throw (TraverseException) {
    if(isTypeOf<Div>(this->exprBeingCompared)){
        PDiv divBeingComp=SPointerCast<Div>(this->exprBeingCompared);
        Comparator cmpL(divBeingComp->lArg);
        Comparator cmpR(divBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpL.areEqual();
        
        this->result = ll && rr;
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstPow expr) throw (TraverseException) {
    if(isTypeOf<Pow>(this->exprBeingCompared)){
        PPow powBeingComp=SPointerCast<Pow>(this->exprBeingCompared);
        Comparator cmpL(powBeingComp->lArg);
        Comparator cmpR(powBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpL.areEqual();
        
        this->result = ll && rr;
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstSin expr) throw (TraverseException) {
    if(isTypeOf<Sin>(this->exprBeingCompared)){
        PSin sinBeingComp=SPointerCast<Sin>(this->exprBeingCompared);
        Comparator cmp(sinBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstCos expr) throw (TraverseException) {
    if(isTypeOf<Cos>(this->exprBeingCompared)){
        PCos cosBeingComp=SPointerCast<Cos>(this->exprBeingCompared);
        Comparator cmp(cosBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstTan expr) throw (TraverseException) {
    if(isTypeOf<Tan>(this->exprBeingCompared)){
        PTan tanBeingComp=SPointerCast<Tan>(this->exprBeingCompared);
        Comparator cmp(tanBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstCtan expr) throw (TraverseException) {
    if(isTypeOf<Ctan>(this->exprBeingCompared)){
        PCtan ctanBeingComp=SPointerCast<Ctan>(this->exprBeingCompared);
        Comparator cmp(ctanBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstLn expr) throw (TraverseException) {
    if(isTypeOf<Ln>(this->exprBeingCompared)){
        PLn lnBeingComp=SPointerCast<Ln>(this->exprBeingCompared);
        Comparator cmp(lnBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}
void Comparator::visit(const PConstExp expr) throw (TraverseException) {
    if(isTypeOf<Exp>(this->exprBeingCompared)){
        PExp expBeingComp=SPointerCast<Exp>(this->exprBeingCompared);
        Comparator cmp(expBeingComp->arg);
        expr->arg->traverse(cmp);
        this->result = cmp.areEqual();
        return;
    }
    this->result=false;
}

bool Comparator::areEqual() {
    return this->result;
}

