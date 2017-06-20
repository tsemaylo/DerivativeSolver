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
#include "Constant.h"
#include "Variable.h"
#include "Function.h"
#include "Visitor.h"
#include "TraverseException.h"

using namespace std;

class Differentiator : public Visitor{
private:
	Expression *result; // @TODO what about cleaning?
	string variable;
	
public:
	Differentiator(string var);
	
	/**
	 * @brief Differentiate constant.
	 */
	void visit(const Constant &expr) throw(TraverseException) final;

	/**
	 * @brief Differentiate variable.
	 */
	void visit(const Variable &expr) throw(TraverseException) final;

	/**
	 * @brief Differentiate function.
	 */
	void visit(const Function &expr) throw(TraverseException) final;
	
	void setLastVisitResult(Expression *result);
	
	Expression *getLastVisitResult() const;

};

#endif /* SRC_DIFFERENTIATOR_H_ */
