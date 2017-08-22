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

/**
 * Rule to handle the parsing of elemantary functions of one argument.
 * 
 * It is a templated class (see .tpp for the implementation.
 * 
 * @param Function The class of Expression for the particular function (Sin, Cos, Ln, etc.).
 */
template <class Function>
class RuleFunction : public Rule {
public:
    bool apply(ParserStack& stack, const Token& ) const throw(ParsingException) final;

};

// include the implementation of the template.
#include "RuleFunction.tpp"

#endif /* RULEFUNCTION_H */

