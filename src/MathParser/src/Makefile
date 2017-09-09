include ../config

.PHONY: all obj lib clean

all: obj lib


obj : $(wildcard *.cpp)
	@for f in $^; do\
		echo "Building $$f..." ;\
		$(CXX) $(CXXFLAGS) -c $$f || exit 1;\
		echo " done." ;\
	done

lib : $(wildcard *.o)
	mkdir -p ../$(BUILDDIR)
	$(AR) r ../$(OUT) $^
	$(RANLIB) ../$(OUT)

clean:
	rm -f *.o
	rm -f *.a
