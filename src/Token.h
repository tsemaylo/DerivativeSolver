/**
 * @file   Token.h
 * 
 * @brief  POD for simple token
 * 
 * @since 30.05.2017
 * @author agor
 */

#ifndef TOKEN_H
#define	TOKEN_H

#include <string>

using namespace std;

enum TokenType {
	TNoToken = 0,
	TAlphaNumeric = 1,
	TGroupBracket = 2,
	TOperation = 3,
	TNumeric = 4
};

class Token
{
public:
	const string value;
	const TokenType type;

	Token(string _value, TokenType _type);
};

#endif	/* TOKEN_H */

