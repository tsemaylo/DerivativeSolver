/**
 * @file Constant.h
 *
 * @brief Constants.
 *
 * @since 25.03.2016
 * @author agor
 */

#ifndef SRC_CONSTANT_H_
#define SRC_CONSTANT_H_

#include <memory>
#include "Expression.h"

using namespace std;

class Constant: public Expression, public enable_shared_from_this<Constant> 
{
public:
	const string value;
	
	Constant(string value);

	void traverse(Visitor & ) const throw(TraverseException) final;
	bool isComplete() const final;
};

#endif /* SRC_CONSTANT_H_ */
