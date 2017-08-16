include ../config

.PHONY: all obj app clean

all: obj app

obj : $(wildcard *.cpp)
	@for f in $^; do\
		echo "Building $$f..." ;\
		$(CXX) $(CXXFLAGS) -c $$f || exit 1;\
		echo " done." ;\
	done

app : $(wildcard *.o)
	$(CXX) $(CXXFLAGS) $^ -o ../$(OUT) || exit 1;
	
clean:
	rm -f *.o