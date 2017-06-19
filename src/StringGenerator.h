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

using namespace std;

class StringGenerator : public Visitor{
private:
	string result;
public:	
	void visit(const Constant& expr) final;

	void visit(const Function& expr) final;

	void visit(const Variable& expr) final;
	
	void setLastVisitResult(string result);
	
	string getLastVisitResult() const;
};

#endif /* SRC_STRINGGENERATOR_H_ */
