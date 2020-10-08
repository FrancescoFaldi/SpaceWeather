IDIR =../include
CC=g++
CFLAGS=-I$(IDIR)
CPPFLAGS  += $(shell root-config --cflags)
LDLIBS    += $(shell root-config --libs)
LDFLAGS   += $(shell root-config --ldflags)

%Cint.cxx:Include.h LinkDef.h
	rootcint -f $@ -c $^

ODIR=obj

_DEPS = header.h
DEPS = $(patsubst %,$(IDIR)/%,$(_DEPS))

_OBJ = main.o analisi.o ciclarray.o mean_and_sigma.o
OBJ = $(patsubst %,$(ODIR)/%,$(_OBJ))


$(ODIR)/%.o: %.cpp $(DEPS)
	$(CC) -c -o $@ $< $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(LDFLAGS)

main: $(OBJ)
	$(CC) -o $@ $^ $(CFLAGS) $(CPPFLAGS) $(LDLIBS) $(LDFLAGS)

.PHONY: clean

clean:
	rm -f $(ODIR)/*.o *~ core $(INCDIR)/*~ 
