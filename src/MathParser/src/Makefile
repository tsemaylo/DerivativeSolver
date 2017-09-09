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
	mkdir -p ../$(BUILD_DIR)/include
	$(AR) r ../$(OUT) $^
	$(RANLIB) ../$(OUT)
	cp Pointers.h ../$(BUILD_DIR)/include/
	cp Parser.h ../$(BUILD_DIR)/include/
	cp ParserFactory.h ../$(BUILD_DIR)/include/
	cp ExpressionFactory.h ../$(BUILD_DIR)/include/
	cp Constant.h ../$(BUILD_DIR)/include/
	cp Variable.h ../$(BUILD_DIR)/include/
	cp Sum.h ../$(BUILD_DIR)/include/
	cp Sub.h ../$(BUILD_DIR)/include/
	cp Div.h ../$(BUILD_DIR)/include/
	cp Mult.h ../$(BUILD_DIR)/include/
	cp Pow.h ../$(BUILD_DIR)/include/
	cp Sin.h ../$(BUILD_DIR)/include/
	cp Cos.h ../$(BUILD_DIR)/include/
	cp Tan.h ../$(BUILD_DIR)/include/
	cp Ctan.h ../$(BUILD_DIR)/include/
	cp Ln.h ../$(BUILD_DIR)/include/
	cp Exp.h ../$(BUILD_DIR)/include/
	cp Expression.h ../$(BUILD_DIR)/include/
	cp Visitor.h ../$(BUILD_DIR)/include/
	cp TraverseException.h ../$(BUILD_DIR)/include/
	cp ParsingException.h ../$(BUILD_DIR)/include/

clean:
	rm -f *.o
	rm -f *.a
