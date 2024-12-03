
SUBDIRS := $(wildcard */.)
all : $(SUBDIRS)
.PHONY : fulltest $(SUBDIRS)

$(SUBDIRS) :
	$(MAKE) -s -C $@ clean
	$(MAKE) -C $@ test
	$(MAKE) -s -C $@ clean


	
