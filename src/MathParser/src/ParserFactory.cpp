/**
 * @file ParserFactory.cpp
 * 
 * Implementation of factory to instantiate Parser object.
 * 
 * @author agor
 * @since 09.09.2017
 */

#include "ParserFactory.h"
#include "ParserImpl.h"
#include "Rule.h"


std::unique_ptr<Parser> createParser(){
    return std::move(std::make_unique<ParserImpl>());
}