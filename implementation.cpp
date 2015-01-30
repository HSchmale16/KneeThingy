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
BMA180Accelerometer * g_Accel0; //!< Left Leg Accel
BMA180Accelerometer * g_Accel1; //!< Right Leg Accel
Accel3d g_A3d0;
Accel3d g_A3d1;


// File scope global variables
static sqlite3 *db;

// FWD Declarations of functions used in this file and declared later.


#include <iostream>
// inits the program
int init()
{
	using namespace std;
	// Turn off USR LEDS
	gpio.digitialWrite(	

	// set the pin modes of the GPIOs
	gpio.pinMode(PIN_BUZZER, OUTPUT);
	gpio.pinMode(PIN_CALIB_BUTTON, INPUT);
	gpio.pinMode(PIN_CALIB_LED, OUTPUT);
	gpio.pinMode(PIN_CALIB_DONE_LED, OUTPUT);
	gpio.pinMode(PIN_WARN_LED, OUTPUT);
	gpio.pinMode(PIN_STOP_LED, OUTPUT);
	
	// Init I2C for all devices here
	
	// init first accelerometer
	g_Accel0 = new BMA180Accelerometer(1, 0x38);
	g_Accel0->setRange(PLUSMINUS_1_G);
	g_Accel0->setBandwidth(BW_150HZ);	
	
	// init 2nd accelerometer
	g_Accel1 = new BMA180Accelerometer(1, 0x38);
	g_Accel1->setRange(PLUSMINUS_1_G);
	g_Accel1->setBandwidth(BW_150HZ);

	// init DB
	int rc = sqlite3_open(DB_FILE_PATH.c_str(), &db);
	if(rc){
		exit(0);
	}
		
	return 0;
}

/** This function contains the commands that should be
 * carried out every iteration of the event loop.
 * This function is equilvilent to the arduino `loop()`
 * function.
 */
int eventLoop()
{
	g_Accel0->readFullSensorState();
	float roll = g_Accel0->getPitch();
	float pitch = g_Accel0->getRoll();	
	usleep(UPDATE_WAIT_T); // sleep for a while
	return 0;
}

// accel update function
void updateAccel3d(BMA180Accelerometer *accel,
		Accel3d *a3d)
{
	accel->readFullSensorState();
	a3d->m_roll = accel->getRoll();
	a3d->m_pitch = accel->getPitch();
	a3d->m_xAcc = accel->getAccelerationX();
	a3d->m_yAcc = accel->getAccelerationY();
	a3d->m_zAcc = accel->getAccelerationZ();
}

// inits an accel3d instance
void initAccel3d(BMA180Accelerometer *accel,
		Accel3d *a3d)
{
	accel->readFullSensorState();
	a3d->m_initRoll = accel->getRoll();
	a3d->m_initPitch = accel->getPitch();
	a3d->m_initX = accel->getAccelerationX();
	a3d->m_initY = accel->getAccelerationY();
	a3d->m_initZ = accel->getAccelerationZ();	
}

// Performs a test on the accelerometers
bool testAccel3ds(Accel3d *aLeft, Accel3d *aRight)
{
	return false; // all is right in the world
}


