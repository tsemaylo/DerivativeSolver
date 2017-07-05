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
public:	
	void visit(const Constant& expr) throw(TraverseException) final;

	void visit(const Variable& expr) throw(TraverseException) final;
	
	void visit(const Sum& expr) throw(TraverseException) final;
	void visit(const Sub& expr) throw(TraverseException) final;
	void visit(const Div& expr) throw(TraverseException) final;
	void visit(const Mult& expr) throw(TraverseException) final;
	
	void setLastVisitResult(string result);
	
	string getLastVisitResult() const;
};

#endif /* SRC_STRINGGENERATOR_H_ */
