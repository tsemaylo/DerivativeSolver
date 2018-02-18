/* Licensed to Oleg Tsemaylo under the MIT license.
 * Refer to the LICENSE.txt file in the project root for more information.
 */

/**
 * @file   Token.cpp
 * 
 * @brief  POD for simple token
 * 
 * @since 30.05.2017
 * @author agor
 */

#include "Token.h"

Token::Token(string _value, TokenType _type) : value(_value), type(_type) {}

bool Token::isFunction() const {
    if(this->type != TAlphaNumeric){
        return false;
    }

    if(this->value == "sin" ){
        return true;
    }
    
    if(this->value == "cos"){
        return true;
    }
    
    if(this->value == "tan"){
        return true;
    }
    
    if(this->value == "ctan"){
        return true;
    }
    
    if(this->value == "ln"){
        return true;
    }
    
    if(this->value == "exp"){
        return true;
    }
    
    return false;
}