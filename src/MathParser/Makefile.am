ACLOCAL_AMFLAGS = -I m4 --install
lib_LIBRARIES = libagmathparser.a
include_HEADERS = src/Pointers.h \
		src/Parser.h  \
		src/ParserFactory.h \
		src/ExpressionFactory.h \
		src/Constant.h \
		src/Variable.h \
		src/Sum.h \
		src/Sub.h \
		src/Div.h \
		src/Mult.h \
		src/Pow.h \
		src/Sin.h \
		src/Cos.h \
		src/Tan.h \
		src/Ctan.h \
		src/Ln.h \
		src/Exp.h \
		src/Expression.h \
		src/Visitor.h \
		src/TraverseException.h \
		src/ParsingException.h
	
libagmathparser_a_SOURCES = src/ParserFactory.cpp \
		src/Expression.cpp \
		src/RuleSubLV.h \
		src/RuleMultRV.h \
		src/RuleSubRV.h \
		src/RuleMultLV.cpp \
		src/Ln.cpp \
		src/Sub.h \
		src/Div.cpp \
		src/Comparator.cpp \
		src/RulePowRV.cpp \
		src/Exp.h \
		src/Comparator.h \
		src/ParserImpl.h \
		src/RuleSumLV.h \
		src/Pow.cpp \
		src/Visitor.h \
		src/RuleSubRV.cpp \
		src/TraverseException.h \
		src/Sum.h \
		src/Sin.h \
		src/StringGenerator.h \
		src/ParserStack.cpp \
		src/RuleSubLV.cpp \
		src/ParsingException.cpp \
		src/RuleFunction.tpp \
		src/Rule.h \
		src/Cos.h \
		src/RuleDivLV.h \
		src/RuleDivRV.h \
		src/Pointers.h \
		src/ExpressionFactory.cpp \
		src/Parser.h \
		src/Ln.h \
		src/Variable.cpp \
		src/ParserImpl.cpp \
		src/Expression.h \
		src/Sub.cpp \
		src/ExpressionFactory.h \
		src/ExceptionThrower.h \
		src/RuleSumRV.cpp \
		src/RuleOperations.h \
		src/RulePowRV.h \
		src/TraverseException.cpp \
		src/RuleDivRV.cpp \
		src/Ctan.cpp \
		src/RuleSumLV.cpp \
		src/Tan.h \
		src/Token.h \
		src/Constant.h \
		src/RuleMultRV.cpp \
		src/RulePowLV.h \
		src/ParserFactory.h \
		src/Token.cpp \
		src/ParsingException.h \
		src/RuleMultLV.h \
		src/Mult.cpp \
		src/Mult.h \
		src/Sin.cpp \
		src/Pow.h \
		src/Cos.cpp \
		src/Constant.cpp \
		src/RuleOperations.tpp \
		src/StringGenerator.cpp \
		src/Div.h \
		src/Ctan.h \
		src/RulePowLV.cpp \
		src/Tan.cpp \
		src/Variable.h \
		src/RuleFunction.h \
		src/Rule.cpp \
		src/RuleSumRV.h \
		src/Sum.cpp \
		src/RuleDivLV.cpp \
		src/Exp.cpp \
		src/ParserStack.h 

libagmathparser_a_CXXFLAGS = -Wall -Werror -Wextra -Wpedantic -O0 -ggdb

noinst_PROGRAMS = ParserTest
ParserTest_SOURCES = test/ParserTest.cpp
ParserTest_CXXFLAGS = -Wall -Werror -Wextra -Wpedantic -O0 -ggdb


