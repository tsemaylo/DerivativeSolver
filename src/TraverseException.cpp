/**
 * @file   TraverseException.cpp
 * 
 * Base class for exception caused by traverse of syntax tree (Expression subtypes).
 *
 * @since 20.06.2017
 * @author agor
 */

#include "TraverseException.h"

const char* TraverseException::what() const noexcept{
	return this->message.c_str();
}
