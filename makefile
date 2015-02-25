# Makefile for KneeThing
# @author Henry J Schmale
# @date January 25, 2015

CXX=g++

CXX_FLAGS=-O2

LD_FLAGS= -lsqlite3

SRC=main.cpp \
    implementation.cpp \
    sqlCallbacks.cpp \
    src/BMA180Accelerometer.cpp \
    src/gnublin.cpp 

OBJ=$(SRC:.cpp=.o)

EXE=KneeThing.out

# Location to deploy to
DEPLOY_LOC=root@192.168.7.2:/root/KneeThingy

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LD_FLAGS) -o $@ $(OBJ)

.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

# Removes the object files and the executables
clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o
	#rm -rf BlackLib/*.o

# Copies the program to a connected beagle bone
deploy: clean
	cd ..
	rsync -r * $(DEPLOY_LOC)
	#ssh root@192.168.7.2 "cd $(DEPLOY_LOC) ; make all"
