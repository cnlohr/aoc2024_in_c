
SUBDIRS := $(wildcard */.)
all : $(SUBDIRS)
.PHONY : fulltest $(SUBDIRS)

profile.txt : $(SUBDIRS)

OP=
ifeq ($(AOCPROF),)
	OP=test
else
	OP=testinput
endif

$(SUBDIRS) :
	$(MAKE) -s -C $@ clean
	$(MAKE) -C $@ $(OP) 2>&1 | tee -a profile.txt
	$(MAKE) -s -C $@ clean

# AOCPROF=1 make csv.csv
csv.csv : profile.txt
	grep PROFILE profile.txt > csv.csv
	rm profile.txt

clean :
	rm profile.txt
