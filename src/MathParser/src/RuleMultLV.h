/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   RuleMultLV.h
 * 
 * Grammar rule to handle multiplication operation for left hand operand (definition).
 * 
 * @since 14.08.2017
 * @author agor
 */

#ifndef RULEMULTLV_H
#define RULEMULTLV_H

#include "RuleOperations.h"

class Mult;

class RuleMultLV : public RuleOperations<Mult, false> {
 
private:
    bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) final;
};

#endif /* RULEMULTLV_H */

