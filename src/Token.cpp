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
    
    if(this->value.find("sin", 0) == 0){
        return true;
    }
    
    if(this->value.find("cos", 0) == 0){
        return true;
    }
    
    if(this->value.find("tan", 0) == 0){
        return true;
    }
    
    if(this->value.find("ctan", 0) == 0){
        return true;
    }
    
    if(this->value.find("ln", 0) == 0){
        return true;
    }
    
    if(this->value.find("exp", 0) == 0){
        return true;
    }
    
    return false;
}