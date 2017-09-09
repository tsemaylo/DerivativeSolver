include ../config

.PHONY: all gtest createBuildDir testCases buildTests linkTests clean run 

OBJFILES = $(patsubst ../$(SRC)/main.o, ,$(wildcard ../$(SRC)/*.o))

all: gtest createBuildDir buildTests run

gtest:
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -isystem=$(GTEST) -c $(GTEST)/src/gtest-all.cc -o gtest-all.o
	$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -c $(GTEST)/src/gtest_main.cc -o gtest_main.o

run: 
	@for f in ../$(BUILDDIR)/tests/*; do\
		$$f --gtest_shuffle --gtest_repeat=10 || exit 1;\
	done
	
createBuildDir:
	mkdir -p ../$(BUILDDIR)/tests 

buildTests: $(wildcard *.cpp)
	@for f in $^; do\
		echo "Building $$f..." ;\
		$(CXX) $(CXXFLAGS) -isystem=$(GTEST)/include -I ../$(SRC) -I$(LIBDIR)/include/MathParser -c $$f  || exit 1;\
		$(CXX) $(CXXFLAGS) $(OBJFILES) $${f%.*}.o gtest-all.o gtest_main.o $(LIBDIR)/MathParser.a -lpthread -o ../$(BUILDDIR)/tests/$${f%.*}  || exit 1;\
		echo " done." ;\
	done

clean:
	rm -f *.o 
	rm -fr ../$(BUILDDIR)/tests