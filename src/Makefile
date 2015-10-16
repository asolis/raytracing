# Rules
include ../Makefile.rules

BINDIR=../bin

VPATH=$(BINDIR)

DIRS=

SRC= vec3.cpp camera.cpp configreader.cpp frame.cpp disc.cpp main.cpp plane.cpp scene.cpp sphere.cpp triangle.cpp box.cpp

OBJ=$(SRC:%.cpp=%.o) $(SRC:%.c=%.o)

all: $(OBJ)
	for i in $(DIRS); do make -C $$i; done


-include makefile.depend

depend: $(SRC) 
	$(CXX) $(INCDIR) -MG -MM $(SRC) >Makefile.depend
	for i in $(DIRS); do make depend -C $$i; done

clean:
	rm -f *~ *.o
	for i in $(DIRS); do make clean -C $$i; done

.PHONY: clean

