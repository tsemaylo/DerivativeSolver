/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file RuleNoSignMult.h
 * 
 * The definition of RuleNoSignMult.
 * 
 * @author  agor
 * @since 12.12.2017
 */

#ifndef RULENOSIGNMULT_H
#define RULENOSIGNMULT_H

#include "Rule.h"

/**
 * Rule is intended to reduce the two adjacent completed expression into one multiplication.
 * 
 * Indead, if two expressions are already parsed, but no operator stays in between,
 * then we can consider a multiplication of these two terms.
 */
class RuleNoSignMult : public Rule {
public:
    bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) final;
};

#endif /* RULENOSIGNMULT_H */

