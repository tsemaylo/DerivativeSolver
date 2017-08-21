/**
 * @file RuleFunction.h
 * 
 * The definition of RuleFunction.
 * 
 * @author  agor
 * @since 21.08.2017
 */

#ifndef RULEFUNCTION_H
#define RULEFUNCTION_H

#include "Rule.h"

template <class Function>
class RuleFunction : public Rule {
public:

    bool apply(ParserStack& stack, const Token& lookAheadToken) const throw(ParsingException) final;

};

#endif /* RULEFUNCTION_H */

