include ../config

.PHONY: all obj app clean

all: obj app

obj : $(wildcard *.cpp)
	@for f in $^; do\
		$(CXX) $(CXXFLAGS) -c $$f || exit 1;\
	done

app : $(wildcard *.o)
	$(CXX) $(CXXFLAGS) $^ -o ../$(OUT) || exit 1;
	
clean:
	rm -f *.o