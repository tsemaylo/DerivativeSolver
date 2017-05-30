include ../config

.PHONY: all obj app clean

all: obj app

obj : $(wildcard *.cpp)
	@for f in $^; do\
		$(CXX) $(CXXFLAGS) -c $$f ;\
	done

app : main.cpp
	$(CXX) $(CXXFLAGS) -o main.o -c $^
	$(CXX) $(CXXFLAGS) $(wildcard *.o) -o ../$(OUT)

clean:
	rm -f *.o