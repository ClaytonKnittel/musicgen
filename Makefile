GC=gcc
GP=g++
EXE=mpl
CPPFLAGS=-std=c++17 -g
CFLAGS=-g

SDIR=.
ODIR=.obj

CSDIR=.
CODIR=.obj

SRC=$(wildcard $(SDIR)/*.cpp)
OBJ=$(patsubst $(SDIR)/%.cpp,$(ODIR)/%.o,$(SRC))
DEP=$(wildcard $(IDIR)/*.hpp)

CSRC=$(wildcard $(CSDIR)/*.c)
COBJ=$(patsubst $(CSDIR)/%.c,$(CODIR)/%.o,$(CSRC))
CDEP=$(wildcard $(CIDIR)/*.h)

$(EXE): $(OBJ) $(COBJ)
	$(GP) $(OBJ) $(COBJ) -o $@

$(ODIR)/%.o: $(SDIR)/%.cpp
	$(GP) $(CPPFLAGS) -c $< -o $@

$(CODIR)/%.o: $(CSDIR)/%.c
	$(GC) $(CFLAGS) -c $< -o $@

-include $(wildcard $(ODIR)/*.d)

.PHONY: clean
clean:
	-rm -f $(ODIR)/*.o $(ODIR)/*.d *~ core $(IDIR)/*~ rel
