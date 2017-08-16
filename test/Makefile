include ../config

.PHONY: all gtest createBuildDir testCases clean run $(UNITS)

OBJFILES = $(patsubst ../$(SRC)/main.o, ,$(wildcard ../$(SRC)/*.o))

all: gtest testCases run

gtest:
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -isystem=$(GTEST) -c $(GTEST)/src/gtest-all.cc -o gtest-all.o
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o gtest_main.o

testCases: createBuildDir buildTests linkTests

createBuildDir:
	mkdir -p ../$(BUILD_DIR)/tests ;\

buildTests: $(wildcard *.cpp)
	@for f in $^; do\
		echo "Building $$f..." ;\
		$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -c $$f  || exit 1;\
		echo " done." ;\
	done

linkTests: $(wildcard *Test.o)
	@for f in $^; do\
		echo "Linking $$f..." ;\
		$(CXX) $(CXXFLAGS) $(OBJFILES) $$f gtest-all.o gtest_main.o -lpthread -o ../$(BUILD_DIR)/tests/$${f%.*}  || exit 1;\
		echo " done." ;\
	done
	
run:
	@for f in ../$(BUILD_DIR)/tests/*; do\
		$$f || exit 1;\
	done
	
clean:
	rm -f *.o 