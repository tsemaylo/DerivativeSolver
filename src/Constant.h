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
	Constant(string name);

	void accept(Visitor & ) const final;
};

#endif /* SRC_CONSTANT_H_ */
