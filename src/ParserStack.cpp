/**
 * @file   ParserStack.cpp
 * 
 * @brief  The data type stack of terminals and non-terminals used by parser and his rules.
 * 
 * @since 09.08.2017
 * @author agor
 */

#include "ParserStack.h"
#include "StringGenerator.h"

#include <string>

string to_string(const ParserStack &stack) {
    return to_string(stack.begin(), stack.end());
}

string to_string(ParserStack::const_iterator start, ParserStack::const_iterator end) {
    string out = "";
    for (; start != end; ++start) {
        out += to_string(*start);
    }
    return out;
}
