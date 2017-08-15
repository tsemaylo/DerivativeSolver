include ../config

UNITS= Parser Rule RuleMultRV RuleMultLV RuleDivRV RuleDivLV RuleSumLV RuleSumRV RuleSubLV RuleSubRV StringGenerator

.PHONY: all gtest buildDir testCases clean run $(UNITS)

OBJFILES = $(patsubst ../$(SRC)/main.o, ,$(wildcard ../$(SRC)/*.o))

all: gtest testCases run

gtest:
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -isystem=$(GTEST) -c $(GTEST)/src/gtest-all.cc -o gtest-all.o
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o gtest_main.o

testCases: buildDir $(UNITS)

buildDir:
	mkdir -p ../$(BUILD_DIR)/tests ;\
		
Parser: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 

Rule: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 
	
RuleMultLV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 

RuleMultRV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 

RuleDivLV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 

RuleDivRV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 
	
RuleSumLV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 
	
RuleSumRV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 

RuleSubLV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 
	
RuleSubRV: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test 
	
StringGenerator: 
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $@Test.cpp -o $@Test.o ;\
	$(CXX) $(CXXFLAGS) $(OBJFILES) $@Test.o gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$@Test
	
run:
	@for f in ../$(BUILD_DIR)/tests/*; do\
		$$f || exit 1;\
	done
	
clean:
	rm -f *.o 