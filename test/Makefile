include ../config

UNITS= Parser RuleSumLV RuleSumRV StringGenerator

.PHONY: all gtest buildDir testCases clean run $(UNITS)

all: gtest testCases run

gtest:
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -isystem=$(GTEST) -c $(GTEST)/src/gtest-all.cc -o gtest-all.o
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o gtest_main.o

testCases: buildDir $(UNITS)

buildDir:
	mkdir -p ../$(BUILD_DIR)/tests ;\
		
Parser: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS)  $(addprefix ../$(SRC)/, RuleSumLV.o RuleSumRV.o ParserStack.o TraverseException.o ParsingException.o Parser.o Token.o Variable.o Sum.o Sub.o Mult.o Div.o Constant.o Expression.o StringGenerator.o Differentiator.o) $@Test.o gtest-all.o gtest_main.o -lpthread  -o ../$(BUILD_DIR)/tests/$@Test 

RuleSumLV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS)  $(addprefix ../$(SRC)/, RuleSumLV.o ParserStack.o StringGenerator.o TraverseException.o ParsingException.o Variable.o Sum.o Expression.o) $@Test.o gtest-all.o gtest_main.o -lpthread  -o ../$(BUILD_DIR)/tests/$@Test 
	
RuleSumRV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS)  $(addprefix ../$(SRC)/, RuleSumRV.o ParserStack.o StringGenerator.o TraverseException.o ParsingException.o Variable.o Sum.o Expression.o) $@Test.o gtest-all.o gtest_main.o -lpthread  -o ../$(BUILD_DIR)/tests/$@Test 

StringGenerator: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS)  $(addprefix ../$(SRC)/, StringGenerator.o ParserStack.o ParsingException.o TraverseException.o Variable.o Sum.o Sub.o Mult.o Div.o Constant.o Expression.o) $@Test.o gtest-all.o gtest_main.o -lpthread  -o ../$(BUILD_DIR)/tests/$@Test
	
run:
	@for f in ../$(BUILD_DIR)/tests/*; do\
		$$f || exit 1;\
	done
	
clean:
	rm -f *.o 