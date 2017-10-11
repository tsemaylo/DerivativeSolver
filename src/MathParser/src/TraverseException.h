/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   TraverseException.h
 * 
 * Base class for exception caused by traverse of syntax tree (Expression subtypes).
 *
 * @since 20.06.2017
 * @author agor
 */

#ifndef TRAVERSEEXCEPTION_H
#define TRAVERSEEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class TraverseException : public exception {
private:
    string message;
public:
    TraverseException(string basicMessage, string context);
    virtual const char* what() const noexcept;
};

#endif /* TRAVERSEEXCEPTION_H */

