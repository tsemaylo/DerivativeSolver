/**
 * @file StringGenerator.h
 * @brief Intergace of the generator of a string representation of an Expression.
 * @since 26.03.2016
 * @author agor
 */

#ifndef SRC_STRINGGENERATOR_H_
#define SRC_STRINGGENERATOR_H_

#include <string>
#include "Expression.h"
#include "Visitor.h"
#include "TraverseException.h"

using namespace std;

class StringGenerator : public Visitor{
private:
	string result;
	
	string getArgString(const shared_ptr<const Expression> argExpr) throw(TraverseException);
	
	template <typename OpClass>
	void visitArythmeticalOp(const shared_ptr<const OpClass> expr, string op) throw(TraverseException);
	
public:	
	void visit(const shared_ptr<const Constant> expr) throw(TraverseException) final;

	void visit(const shared_ptr<const Variable> expr) throw(TraverseException) final;
	
	void visit(const shared_ptr<const Sum> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Sub> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Div> expr) throw(TraverseException) final;
	void visit(const shared_ptr<const Mult> expr) throw(TraverseException) final;
	
	void setLastVisitResult(string result);
	
	string getLastVisitResult() const;
};

#endif /* SRC_STRINGGENERATOR_H_ */
