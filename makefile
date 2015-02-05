# Makefile for KneeThing
# @author Henry J Schmale
# @date January 25, 2015

CXX=g++

CXX_FLAGS= \
	-Wall \
	-std=c++11

LD_FLAGS=-L/usr/local/lib -lglog -lsqlite3

SRC=main.cpp \
    implementation.cpp \
    sqlCallbacks.cpp \
    src/BMA180Accelerometer.cpp \
    src/gnublin.cpp

OBJ=$(SRC:.cpp=.o)

EXE=KneeThing.out

DEPLOY_LOC=root@192.168.7.2:/root/KneeThingy

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LD_FLAGS) $(OBJ) -o $@

cpp.o:
	$(CXX) $(CXX_FLAGS) -o $@ $<
clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o

# Copies the program to a connected beagle bone
deploy: clean
	cd ..
	scp -r . $(DEPLOY_LOC)
