include ../config


.PHONY: all libs obj app clean

all: libs obj app

libs: MathParser
	mkdir -p $(LIBDIR) || exit 1;
	@for libDir in $^; do\
		echo "Building library $$libDir..." ;\
		(cd $$libDir; make clean all;)|| exit 1;\
		(export DESTDIR=$(LIBDIR); cd $$libDir; make install;)|| exit 1;\
		echo " done." ;\
	done

obj : $(wildcard *.cpp)
	for f in $^; do\
		echo "Building $$f..." ;\
		$(CXX) $(CXXFLAGS) -I$(LIBDIR)/include/MathParser/ -c $$f || exit 1;\
		echo " done." ;\
	done

app : $(wildcard *.o)
	mkdir -p ../$(BUILDDIR) || exit 1;
	$(CXX) $(CXXFLAGS) $^ $(LIBDIR)/MathParser.a -o ../$(OUT) || exit 1;
	
clean:
	rm -f *.o