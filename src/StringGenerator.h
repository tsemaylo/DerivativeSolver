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

using namespace std;

class StringGenerator {
public:
	StringGenerator();
	virtual ~StringGenerator();

	string render(const Expression &expr) const;
};

#endif /* SRC_STRINGGENERATOR_H_ */
