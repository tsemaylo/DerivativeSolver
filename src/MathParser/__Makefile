include config

.PHONY: all obj test lib clean install

HEADERS=$(addprefix $(SRC)/, Pointers.h Parser.h ParserFactory.h ExpressionFactory.h Constant.h Variable.h Sum.h Sub.h Div.h Mult.h Pow.h Sin.h Cos.h Tan.h Ctan.h Ln.h Exp.h Expression.h Visitor.h TraverseException.h ParsingException.h)

all: obj test lib

obj:
	(cd src; make obj;) || exit 1;

test:
	(cd test; make clean all;) || exit 1;

lib:
	(cd src; make lib;)

install:
	(cp $(BUILDDIR)/*.a $(DESTDIR)) || exit 1;
	(mkdir -p $(DESTDIR)/include/MathParser) || exit 1;
	@for f in $(HEADERS); do\
		cp $$f $(DESTDIR)/include/MathParser || exit 1;\
	done

clean:
	rm -f *.o
	rm -fr $(BUILD_DIR)
	(cd src; make clean;) || exit 1;
	(cd test; make clean;) || exit 1;