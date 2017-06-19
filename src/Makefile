include ../config

.PHONY: all obj app clean

all: obj app

obj : $(wildcard *.cpp)
	@for f in $^; do\
		$(CXX) $(CXXFLAGS) -c $$f ;\
	done

app : $(wildcard *.o)
	$(CXX) $(CXXFLAGS) $^ -o ../$(OUT)
	
clean:
	rm -f *.o