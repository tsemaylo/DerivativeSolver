/**
 * @file   TraverseException.h
 * 
 * Base class for exception caused by traverse of syntax tree (Expression subtypes).
 *
 * @since 20.06.2017
 * @author agor
 */

#ifndef TRAVERSEEXCEPTION_H
#define	TRAVERSEEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class TraverseException : public exception
{
private:
	string message;
	
public:
	virtual const char* what() const noexcept;
};

#endif	/* TRAVERSEEXCEPTION_H */

