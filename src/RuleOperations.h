/**
 * @file   RuleOperations.h
 * 
 * @brief Definition of interface for grammar rules handling the paresing of operations.
 * 
 * The term "operations" means in this case anything that has an argument, 
 * particularly arithmetic operations or functions.
 * 
 * @since 15.08.2017
 * @author agor
 */

#ifndef RULEOPERATIONS_H
#define RULEOPERATIONS_H

#include "Rule.h"

/**
 * \brief extension of Rule.
 * 
 * Rule interface is preserved and apply() operation is implemented in this class 
 * since it is generic for all operations. The class is abstract and requires from
 * children (implementation of concrete arithmetical or functional rules) to implement
 * the specific logic of operation in applyRule().
 */
class RuleOperations : public Rule{
public:
    bool apply(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) final;
    
protected:
    RuleOperations(bool isRightHand, ExpressionType operationType);
    
    /**
     * Appy the rule and reduce the stack.
     * 
     * Represents the private virtual interface for specific rule logic.
     * 
     * @param op The iterator of parsing stack pointing to considered operation.
     * @param arg The iterator of parsing stack pointing to the assumed argument of considered operation.
     * @param stack The parsing stack.
     * 
     * @return true if the stack has been reduced.
     */
    virtual bool applyRule(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException) = 0;
    
private:
    bool isRightHand;
    ExpressionType operationType; 
    
    /**
     * The warpper for concrete applyRule(). Implements general logic to check the consistenmcy operation and its arguments before reducing the stack.
     * 
     * @param op The iterator of parsing stack pointing to considered operation.
     * @param arg The iterator of parsing stack pointing to the assumed argument of considered operation.
     * @param stack The parsing stack.
     * 
     * @return true if the stack has been reduced.
     */
    bool applyRuleWrapper(const ParserStack::const_iterator op, const ParserStack::const_iterator arg, ParserStack &stack) const throw (ParsingException);
    
    /**
     * The method iterates through the stack and invokes the application of rule for relevant stack items.
     * 
     * Relevant stack items are the ones which correspond to the operation and 
     * this operation has a priority against the forecoming symbol (lookAheadToken).
     * 
     * @param stack The parsing stack.
     * @param lookAheadToken The next token in the row, to determine the priority of operation.
     * 
     * @return true if the stack has been reduced.
     */
    bool iterateStack(ParserStack &stack, const Token &lookAheadToken) const throw (ParsingException) ;
};

#endif /* RULEOPERATIONS_H */

