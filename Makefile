
SUBDIRS := $(wildcard */.)
all : $(SUBDIRS)
.PHONY : fulltest $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -C $@ clean test
	$(MAKE) -C $@ clean


	
