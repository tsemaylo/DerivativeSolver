include config

.PHONY: all libs obj test app clean 

all: libs obj test app

libs:
	(cd src; make libs;) || exit 1;
	
obj:
	(cd src; make obj;) || exit 1;

test:
	(cd test; make clean all;) || exit 1;
	./testApplication.sh || exit 1;

app:
	(cd src; make app;)

clean:
	rm -f *.o
	rm -fr $(BUILD_DIR)/*
	(cd src; make clean;) || exit 1;
	(cd test; make clean;) || exit 1;