#!/bin/csh

include Makefile.rules

BINDIR=bin

DIRS=src

PROG=raytracer

VPATH=$(BINDIR)


$(PROG): $(BINDIR)/*.o SUBDIR 
	$(CXX) $(LDLIBDIR) -o $(BINDIR)/$(PROG) $(BINDIR)/*.o  


$(BINDIR)/*.o: SUBDIR

SUBDIR:
	for i in $(DIRS); do make -C $$i; done


.PHONY: SUBDIR


depend: 
	for i in $(DIRS); do make depend -C $$i; done


clean:
	for i in $(DIRS); do make clean -C $$i; done
	rm -f $(BINDIR)/*.o $(BINDIR)/$(PROG)


.PHONY: clean
