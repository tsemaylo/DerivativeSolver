/** 
 * @file   Visitor.h
 * 
 * @brief Generic visitor interface.
 *
 * @since 12.06.2017
 * @author agor
 */

#ifndef VISITOR_H
#define	VISITOR_H

#include "Constant.h"
#include "Variable.h"
#include "Sum.h"
#include "Sub.h"
#include "Div.h"
#include "Mult.h"
#include "Pow.h"
#include "Sin.h"
#include "Cos.h"
#include "Tan.h"
#include "Ctan.h"
#include "Ln.h"
#include "Exp.h"
#include "TraverseException.h"

/**
 * Interface for different visitors used to traverse the syntax tree (subtypes of Expression).
 */
class Visitor
{
public:	
	virtual void visit(const PConstConstant expr) throw(TraverseException) = 0;
	virtual void visit(const PConstVariable expr) throw(TraverseException) = 0;
	virtual void visit(const PConstSum expr) throw(TraverseException) = 0;
	virtual void visit(const PConstSub expr) throw(TraverseException) = 0;
	virtual void visit(const PConstDiv expr) throw(TraverseException) = 0;
	virtual void visit(const PConstMult expr) throw(TraverseException) = 0;
        virtual void visit(const PConstPow expr) throw(TraverseException) = 0;
        virtual void visit(const PConstSin expr) throw(TraverseException) = 0;
        virtual void visit(const PConstCos expr) throw(TraverseException) = 0;
        virtual void visit(const PConstTan expr) throw(TraverseException) = 0;
        virtual void visit(const PConstCtan expr) throw(TraverseException) = 0;
        virtual void visit(const PConstLn expr) throw(TraverseException) = 0;
        virtual void visit(const PConstExp expr) throw(TraverseException) = 0;
};

#endif	/* VISITOR_H */

