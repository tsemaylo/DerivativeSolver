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
        return lookAheadToken.isFunction();
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