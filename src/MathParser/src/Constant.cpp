/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file Constant.cpp
 * @brief A constant expression
 * @since 25.03.2016
 * @uthor agor
 */

#include "Constant.h"
#include "Visitor.h"

Constant::Constant() : Expression(EConstant) {
}

Constant::Constant(std::string value) : Expression(EConstant), value(value) {
}

void Constant::traverse(Visitor &visitor) const throw (TraverseException) {
    visitor.visit(shared_from_this());
}

bool Constant::isComplete() const {
    return true;
}