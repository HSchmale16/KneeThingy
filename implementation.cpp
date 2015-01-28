/** Implementation.cpp
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains the implementation of functions defined in default.h
 */

#include "default.h"
#include <sqlite3.h>

// Externs declared in header are here
gnublin_gpio gpio;
gnublin_i2c accel0;
gnublin_i2c accel1;
gnublin_i2c gyro0;
gnublin_i2c gyro1;

// File scope global variables
static sqlite3 *db;

// FWD Declarations of functions used in this file and declared later.



// inits the program
int init()
{
	// set the pin modes of the GPIOs
	gpio.pinMode(PIN_BUZZER, OUTPUT);
	gpio.pinMode(PIN_CALIB_BUTTON, INPUT);
	gpio.pinMode(PIN_CALIB_LED, OUTPUT);
	gpio.pinMode(PIN_CALIB_DONE_LED, OUTPUT);
	gpio.pinMode(PIN_WARN_LED, OUTPUT);
	gpio.pinMode(PIN_STOP_LED, OUTPUT);
	
	// Init I2C for all devices here
	

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


