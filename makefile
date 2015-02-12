# Makefile for KneeThing
# @author Henry J Schmale
# @date January 25, 2015

CXX=g++

CXX_FLAGS=

LD_FLAGS= -lsqlite3

SRC=main.cpp \
    implementation.cpp \
    sqlCallbacks.cpp \
    src/BMA180Accelerometer.cpp \
    BlackLib/BlackADC.cpp \
    BlackLib/BlackCore.cpp \
    BlackLib/BlackGPIO.cpp \
    BlackLib/BlackI2C.cpp \
    BlackLib/BlackPWM.cpp \
    BlackLib/BlackSPI.cpp \
    BlackLib/BlackUART.cpp

OBJ=$(SRC:.cpp=.o)

EXE=KneeThing.out

# Location to deploy to
DEPLOY_LOC=root@192.168.7.2:/root/KneeThingy

all: $(SRC) $(EXE)

$(EXE): $(OBJ)
	$(CXX) $(LD_FLAGS) $(OBJ) -o $@

.cpp.o:
	$(CXX) -c $(CXX_FLAGS) -o $@ $<

# Removes the object files and the executables
clean:
	if [ -e $(EXE) ] ; then rm $(EXE); fi
	rm -rf *.o
	rm -rf src/*.o

# Copies the program to a connected beagle bone
deploy: clean
	cd ..
	scp -r . $(DEPLOY_LOC)
