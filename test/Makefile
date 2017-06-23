include ../config

UNITS= Parser

.PHONY: all gtest buildDir testCases clean $(UNITS)

all: gtest testCases

gtest:
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -isystem=$(GTEST) -c $(GTEST)/src/gtest-all.cc -o gtest-all.o
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o gtest_main.o

testCases: buildDir $(UNITS)

buildDir:
	mkdir -p ../$(BUILD_DIR)/tests ;\
		
Parser: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS)  $(addprefix ../$(SRC)/, RuleSumLV.o RuleSumRV.o TraverseException.o ParsingException.o Parser.o Token.o Variable.o Function.o Constant.o Expression.o StringGenerator.o Differentiator.o) $@Test.o gtest-all.o gtest_main.o -lpthread  -o ../$(BUILD_DIR)/tests/$@Test 
	
clean:
	rm -f *.o 