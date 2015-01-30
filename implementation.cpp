/** Implementation.cpp
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains the implementation of functions defined in default.h
 */

#include "default.h"
#include <sqlite3.h>
#include <unistd.h>

// Externs declared in header are here
gnublin_gpio gpio;
BMA180Accelerometer * g_Accel0;
BMA180Accelerometer * g_Accel1;

// File scope global variables
static sqlite3 *db;

// FWD Declarations of functions used in this file and declared later.


#include <iostream>
// inits the program
int init()
{
	using namespace std;
	// set the pin modes of the GPIOs
	gpio.pinMode(PIN_BUZZER, OUTPUT);
	gpio.pinMode(PIN_CALIB_BUTTON, INPUT);
	gpio.pinMode(PIN_CALIB_LED, OUTPUT);
	gpio.pinMode(PIN_CALIB_DONE_LED, OUTPUT);
	gpio.pinMode(PIN_WARN_LED, OUTPUT);
	gpio.pinMode(PIN_STOP_LED, OUTPUT);
	
	// Init I2C for all devices here
	g_Accel0 = new BMA180Accelerometer(1, 0x38);
	g_Accel0->setRange(PLUSMINUS_1_G);
	g_Accel0->setBandwidth(BW_150HZ);	

	// init DB
	int rc = sqlite3_open(DB_FILE_PATH.c_str(), &db);
	if(rc){
		exit(0);
	}
		
	return 0;
}

// This function contains the commands that should be
// carried out every iteration of the event loop.
// This function is equilvilent to the arduino `loop()`
// function.
int eventLoop()
{
	g_Accel0->readFullSensorState();
	float roll = g_Accel0->getPitch();
	float pitch = g_Accel0->getRoll();
	//std::cout << "Roll: " << roll << "\tPitch: " << pitch << std::endl;	
	usleep(50000);
	return 0;
}


