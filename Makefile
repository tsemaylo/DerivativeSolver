include config

.PHONY: all obj test app clean 

all: obj test app

obj:
	(cd src; make obj;) || exit 1;

test:
	(cd test; make clean all;)

app:
	(cd src; make app;)

clean:
	rm -f *.o
	rm -fr $(BUILD_DIR)/*
	(cd src; make clean;) || exit 1;
	(cd test; make clean;) || exit 1;