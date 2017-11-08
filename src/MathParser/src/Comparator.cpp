/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Comparator.cpp
 * 
 * Implementation of Comparator class. 
 * @author agor
 * @since 09.10.2017
 */

#include "Comparator.h"
#include "ExceptionThrower.h"

Comparator::Comparator(PExpression expr) : exprBeingCompared(expr), result(false) {
}

template<typename T, typename PT>
void Comparator::typeAware(PT expr, std::function<bool (PT, PT)> f)  throw (TraverseException) {
    this->result=false;
    if(expr == nullptr){
        THROW(TraverseException, "Left-hand expression is NULL", "N.A.");
    }
    if(exprBeingCompared == nullptr){
        THROW(TraverseException, "Right-hand expression is NULL", "N.A.");
    }
    
    if(isTypeOf<T>(this->exprBeingCompared)) {
        PT typedExprBeingComp=SPointerCast<T>(this->exprBeingCompared);
        this->result = f(expr, typedExprBeingComp); // лямбды лямбдочки
    }
}

void Comparator::visit(const PConstConstant expr) throw (TraverseException) {
    typeAware<Constant, PConstConstant>(expr, [this] (PConstConstant expr, PConstConstant typedExprBeingComp) -> bool {
        return expr->value == typedExprBeingComp->value;
    });
}

void Comparator::visit(const PConstVariable expr) throw (TraverseException) {
    typeAware<Variable, PConstVariable>(expr, [this] (PConstVariable expr, PConstVariable typedExprBeingComp) -> bool {
       return typedExprBeingComp->name == expr->name; 
    });
}

void Comparator::visit(const PConstSum expr) throw (TraverseException) {
    typeAware<Sum, PConstSum>(expr, [this] (PConstSum expr, PConstSum typedExprBeingComp) -> bool {
        Comparator cmpL(typedExprBeingComp->lArg);
        Comparator cmpR(typedExprBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->lArg->traverse(cmpR);
        bool rl=cmpR.areEqual();
        
        expr->rArg->traverse(cmpL);
        bool lr=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpR.areEqual();
        
        return (ll && rr) || (lr && rl);
    });
}
void Comparator::visit(const PConstSub expr) throw (TraverseException) {
    typeAware<Sub, PConstSub>(expr, [this] (PConstSub expr, PConstSub typedExprBeingComp) -> bool {
        Comparator cmpL(typedExprBeingComp->lArg);
        Comparator cmpR(typedExprBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        expr->rArg->traverse(cmpR);
        
        return cmpL.areEqual() && cmpR.areEqual();
    });
}
void Comparator::visit(const PConstMult expr) throw (TraverseException) {
    typeAware<Mult, PConstMult>(expr, [this] (PConstMult expr, PConstMult typedExprBeingComp) -> bool {
        Comparator cmpL(typedExprBeingComp->lArg);
        Comparator cmpR(typedExprBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        bool ll=cmpL.areEqual();
        expr->lArg->traverse(cmpR);
        bool rl=cmpR.areEqual();
        
        expr->rArg->traverse(cmpL);
        bool lr=cmpL.areEqual();
        expr->rArg->traverse(cmpR);
        bool rr=cmpR.areEqual();
        
        return (ll && rr) || (lr && rl); 
    });
}
void Comparator::visit(const PConstDiv expr) throw (TraverseException) {
    typeAware<Div, PConstDiv>(expr, [this] (PConstDiv expr, PConstDiv typedExprBeingComp) -> bool {
        Comparator cmpL(typedExprBeingComp->lArg);
        Comparator cmpR(typedExprBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        expr->rArg->traverse(cmpR);
        
        return cmpL.areEqual() && cmpR.areEqual();
    });
}
void Comparator::visit(const PConstPow expr) throw (TraverseException) {
    typeAware<Pow, PConstPow>(expr, [this] (PConstPow expr, PConstPow typedExprBeingComp) -> bool {
        Comparator cmpL(typedExprBeingComp->lArg);
        Comparator cmpR(typedExprBeingComp->rArg);
        
        expr->lArg->traverse(cmpL);
        expr->rArg->traverse(cmpR);
        
        return cmpL.areEqual() && cmpR.areEqual();
    });
}

template<typename T, typename PT>
void Comparator::visitFunction(PT expr) throw (TraverseException) {
    typeAware<T, PT>(expr, [this] (PT expr, PT typedExprBeingComp) -> bool {
        Comparator cmp(typedExprBeingComp->arg);
        expr->arg->traverse(cmp);
        return cmp.areEqual();
    });
}

void Comparator::visit(const PConstSin expr) throw (TraverseException) {
    visitFunction<Sin, PConstSin>(expr);
}

void Comparator::visit(const PConstCos expr) throw (TraverseException) {
    visitFunction<Cos, PConstCos>(expr);
}
void Comparator::visit(const PConstTan expr) throw (TraverseException) {
    visitFunction<Tan, PConstTan>(expr);
}
void Comparator::visit(const PConstCtan expr) throw (TraverseException) {
    visitFunction<Ctan, PConstCtan>(expr);
}
void Comparator::visit(const PConstLn expr) throw (TraverseException) {
    visitFunction<Ln, PConstLn>(expr);
}
void Comparator::visit(const PConstExp expr) throw (TraverseException) {
    visitFunction<Exp, PConstExp>(expr);
}

bool Comparator::areEqual() {
    return this->result;
}