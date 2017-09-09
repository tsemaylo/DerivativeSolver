/**
 * @file ParserFactory.cpp
 * 
 * Factory to instantiate Parser object.
 * 
 * @author agor
 * @since 09.09.2017
 */

#ifndef PARSERFACTORY_H
#define PARSERFACTORY_H

#include <memory>
#include "Parser.h"

std::unique_ptr<Parser> createParser();

#endif /* PARSERFACTORY_H */

