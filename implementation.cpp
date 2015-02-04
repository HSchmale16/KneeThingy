/** Implementation.cpp
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains the implementation of functions defined in default.h
 */

#include "default.h"
//#include <sqlite3.h>
#include <unistd.h>

// Externs declared in header are here
gnublin_gpio gpio;
gnublin_adc adc;
BMA180Accelerometer * g_Accel0; //!< Left Leg Accel
BMA180Accelerometer * g_Accel1; //!< Right Leg Accel
Accel3d g_A3d0;
Accel3d g_A3d1;
int HallEffectSensorVal;       //!< The current value of the hall sensor
int initHallEffectSensorVal;   //!< The initial value of the hall sensor

// File scope global variables
//static sqlite3 *db;

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
	
	// Init the hall effect sensor for distance measurement
	initHallEffectSensor();
	
	// Init I2C for all devices here
	
	// init first accelerometer
	g_Accel0 = new BMA180Accelerometer(ACC0_I2C_BUS, ACC0_I2C_ADDY);
	g_Accel0->setRange(PLUSMINUS_1_G);
	g_Accel0->setBandwidth(BW_150HZ);	
	
	// init 2nd accelerometer
	g_Accel1 = new BMA180Accelerometer(ACC1_I2C_BUS, ACC1_I2C_ADDY);
	g_Accel1->setRange(PLUSMINUS_1_G);
	g_Accel1->setBandwidth(BW_150HZ);

	// init DB
	int rc = 0; // sqlite3_open(DB_FILE_PATH.c_str(), &db);
	if(rc)
	{
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
	// Update the data
	updateAccel3d(g_Accel0, &g_A3d0); // update left leg
	updateAccel3d(g_Accel1, &g_A3d1); // update right leg
	/// \todo add a magnetic check
	
	// TEST the values to make sure there within the acceptable range
	bool accelsOk = testAccel3ds(&g_A3d0, &g_A3d1);
	bool distsOk = testHallEffectSensor();	

	// Output the data	
	cout << g_A3d0.m_roll << "  " << g_A3d1.m_roll << endl;
	usleep(UPDATE_WAIT_T); // sleep for a couple of microsecs
	return 0;
}

// ====================================================================
// Updaters and testers
// --------------------------------------------------------------------
// Hall Effect Sensor Functions

// inits hall effect sensor
void initHallEffectSensor()
{
	initHallEffectSensorVal = adc.getVoltage(HALL_EFFECT_SENSOR_PIN);
}

// updates hall effect sensor
void updateHallEffectSensor()
{
	HallEffectSensorVal = adc.getVoltage(HALL_EFFECT_SENSOR_PIN);	
}

// check if the hall effect is still in the good range
bool testHallEffectSensor()
{
	return false; // it's all good take no action
}

// --------------------------------------------------------------------
// Accelerometer Functions

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


