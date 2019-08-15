GC=gcc
GP=g++
EXE=mpl

ifeq ($(DEBUG), 1)
CPPFLAGS=-std=c++17 -MMD -g -O0 -D DEBUG=1
CFLAGS=-g -MMD -O0
else
CPPFLAGS=-std=c++17 -MMD -O2
CFLAGS=-g -MMD -O2
endif


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
