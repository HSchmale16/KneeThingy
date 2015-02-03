# Makefile for KneeThing
# @author Henry J Schmale
# @date January 25, 2015

CXX=g++

CXX_FLAGS= \
	-Wall \
	-std=c++11

LD_FLAGS=

SRC=main.cpp \
    implementation.cpp \
    sqlCallbacks.cpp \
    src/BMA180Accelerometer.cpp \
    src/gnublin.cpp

OBJ=$(SRC:.cpp=.o)

EXE=KneeThing.out

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LD_FLAGS) $(OBJ) -o $@

cpp.o:
	$(CXX) $(CXX_FLAGS) -o $@ $<

clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o
