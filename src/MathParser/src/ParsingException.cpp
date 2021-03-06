/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   ParsingException.cpp
 * 
 * Base class for parsing exceptions 
 * 
 * @since 20.06.2017
 * @author agor
 */

#include "ParsingException.h"

ParsingException::ParsingException(string basicMessage, string stackContent) : message(basicMessage + " Context: " + stackContent) {
}

const char* ParsingException::what() const noexcept {
    return this->message.c_str();
}
