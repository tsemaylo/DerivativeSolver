/**
 * @file   ParsingException.cpp
 * 
 * Base class for parsing exceptions 
 * 
 * @since 20.06.2017
 * @author agor
 */

#include "ParsingException.h"

ParsingException::ParsingException(string message) : message(message) {}

const char* ParsingException::what() const noexcept{
	return this->message.c_str();
}
