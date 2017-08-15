/**
 * @file   Rule.cpp
 * 
 * @brief Implementation of operations related to generic rule management.
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "Rule.h"

bool hasPriority(const ExpressionType exprType, const Token &lookAheadToken) {
    if(exprType == ESum || exprType == ESub){
        if (lookAheadToken.type == TAlphaNumeric) {
            return lookAheadToken.isFunction();
        }
        if(lookAheadToken.type == TOperation){
            return (lookAheadToken.value == "*" || 
                    lookAheadToken.value == "/" || 
                    lookAheadToken.value == "\\" || 
                    lookAheadToken.value == "^");
        }
    }
    
    if(exprType == EMult || exprType == EDiv){
        if (lookAheadToken.type == TAlphaNumeric) {
            return lookAheadToken.isFunction();
        }
        if(lookAheadToken.type == TOperation){
            return (lookAheadToken.isFunction() || lookAheadToken.value == "^");
        }
    }
    
    // @TODO Uncomment when it will be implemented
//    if(exprType == EPow ){
//        if(lookAheadToken.isFunction()){
//            return true;
//        }
//    }
    
    return false;
}