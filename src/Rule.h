/**
 * @file   Rule.h
 * 
 * @brief Interface for parsing rules. And generic operations related to rules.
 * 
 * @since 01.06.2017
 * @author agor
 */

#ifndef RULE_H
#define RULE_H

#include <list>
#include <memory>
#include "Expression.h"
#include "ParsingException.h"
#include "ParserStack.h"
#include "Token.h"

using namespace std;

/**
 * Represents the interface for any possible parsing rule.
 */
class Rule {
public:
    virtual bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) = 0;
};

/**
 * Look at the token ahead and decide whether the next operation in the stack will have more priority then the current one.
 * 
 * @param ExpressionClass The class type of current one .
 * @param lookAheadToken The token that is considered to be an upcoming operation.
 * 
 * @return true if the operation with high priority comes next, otherwise false.
 */
template <class ExpressionClass>
bool hasPriority(const Token &lookAheadToken);

#endif /* RULE_H */

