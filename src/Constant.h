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

#include "Expression.h"

using namespace std;

class Constant: public Expression
{
public:
	const string value;
	
	Constant(string value);

	void traverse(Visitor & ) const throw(TraverseException) final;
};

#endif /* SRC_CONSTANT_H_ */
