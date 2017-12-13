/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   Rule.cpp
 * 
 * @brief Implementation of operations related to generic rule management.
 * 
 * @since 14.08.2017
 * @author agor
 */

#include "Rule.h"

#include "ParserStack.h"
#include "Token.h"
#include "ParserStack.h"
#include "Sum.h"
#include "Sub.h"
#include "Div.h"
#include "Mult.h"
#include "Pow.h"
#include "Sin.h"

template<>
bool hasPriority<Sum>(const Token &lookAheadToken) {
    if (lookAheadToken.type == TAlphaNumeric) {
        // that means, that any following alphanummeric symbol has a priority
        // against addition operations (+ and -)
        // it can either a function or constannt or variable
        // in these cases it can happen, that user omited multiplication sign 
        // and we should consider this implicitly
        return true; 
    }
    if (lookAheadToken.type == TGroupBracket) {
        return true; 
    }
    if (lookAheadToken.type == TOperation) {
        return (lookAheadToken.value == "*" ||
                lookAheadToken.value == "/" ||
                lookAheadToken.value == "\\" ||
                lookAheadToken.value == "^");
    }
    return false;
}

template<>
bool hasPriority<Sub>(const Token &lookAheadToken) {
    return hasPriority<Sum>(lookAheadToken);
}

template<>
bool hasPriority<Mult>(const Token &lookAheadToken) {
    if (lookAheadToken.type == TAlphaNumeric) {
        return lookAheadToken.isFunction();
    }
    if (lookAheadToken.type == TOperation) {
        return (lookAheadToken.isFunction() || lookAheadToken.value == "^");
    }
    return false;
}

template<>
bool hasPriority<Div>(const Token &lookAheadToken) {
    return hasPriority<Mult>(lookAheadToken);
}

template<>
bool hasPriority<Pow>(const Token &lookAheadToken) {
    if (lookAheadToken.type == TAlphaNumeric && lookAheadToken.isFunction()) {
        return true;
    }
    return false;
}