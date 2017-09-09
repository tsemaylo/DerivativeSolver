include config

.PHONY: all obj test lib clean install

all: obj test lib

obj:
	(cd src; make obj;) || exit 1;

test:
	(cd test; make clean all;) || exit 1;

lib:
	(cd src; make lib;)

install:
	(cp $(BUILD_DIR)/*.a $(DESTDIR)) || exit 1;
	(cp -r $(BUILD_DIR)/include $(DESTDIR)) || exit 1;

clean:
	rm -f *.o
	rm -fr $(BUILD_DIR)
	(cd src; make clean;) || exit 1;
	(cd test; make clean;) || exit 1;