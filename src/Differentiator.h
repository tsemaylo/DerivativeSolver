/**
 * @file Differentiator.h
 *
 * @brief Interface for differentiating Visitor for Expression tree.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_DIFFERENTIATOR_H_
#define SRC_DIFFERENTIATOR_H_

#include "Expression.h"
#include "Visitor.h"
#include "TraverseException.h"

using namespace std;

class Differentiator : public Visitor{
private:
	shared_ptr<Expression> result; 
	string variable;
	
public:
	Differentiator(string var);

	void visit(const shared_ptr<const Constant> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Variable> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Sum> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Sub> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Mult> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Div> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Pow> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Sin> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Cos> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Tan> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Ctan> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Ln> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Exp> expr) throw(TraverseException) final;
        
	void setLastVisitResult(const shared_ptr<Expression> result);
	
	shared_ptr<Expression> getLastVisitResult() const;

};

#endif /* SRC_DIFFERENTIATOR_H_ */
