/**
 * @file   ParsingException.h
 * 
 * Base class for parsing exceptions 
 * 
 * @since 20.06.2017
 * @author agor
 */

#ifndef PARSINGEXCEPTION_H
#define	PARSINGEXCEPTION_H

#include <exception>
#include <string>

using namespace std;

class ParsingException : public exception
{
private:
	string message;
public:
	ParsingException(string basicMessage, string stackContent);
	virtual const char* what() const noexcept;
};

#endif	/* PARSINGEXCEPTION_H */

