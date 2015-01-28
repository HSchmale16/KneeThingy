/** Implementation.cpp
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains the implementation of functions defined in default.h
 */

#include "default.h"
#include <sqlite3.h>

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
	/*
	g_Accel0 = new BMA180Accelerometer(0, 0x50);	
	// @todo init g_Accel1
g_Accel0->setRange(PLUSMINUS_1_G);
g_Accel0->setBandwidth(BW_150HZ);
cout << "The current bandwidth is: " << (int)g_Accel0->getBandwidth() << endl;
cout << "The current mode is: " << (int)g_Accel0->getModeConfig() << endl;
cout << "The current range is: " << (int)g_Accel0->getRange() << endl;
cout << "The current temperature is: " << (float)g_Accel0->getTemperature() << endl;
*/
BMA180Accelerometer accelerometer(3, 0x40);
accelerometer.setRange(PLUSMINUS_1_G);
accelerometer.setBandwidth(BW_150HZ);
cout << "The current bandwidth is: " << (int)accelerometer.getBandwidth() << endl;
cout << "The current mode is: " << (int)accelerometer.getModeConfig() << endl;
cout << "The current range is: " << (int)accelerometer.getRange() << endl;
cout << "The current temperature is: " << (float)accelerometer.getTemperature() << endl;
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
	
	return 0;
}


