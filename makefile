# Makefile for KneeThing
# @author Henry J Schmale
# @date January 25, 2015

CXX=g++
CFLAGS=-Wall -std=C++11
LDFLAGS=
SRC=main.cpp gnublin.cpp implementation.cpp
OBJ=$(SRC:.cpp=.o)
EXE=KneeThing.out

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LDFLAGS) $(OBJ) -o $@

.o:
	$(CXX) $(CFLAGS) $< -o $@

clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
