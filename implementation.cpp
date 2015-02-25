/** Implementation.cpp
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains the implementation of functions defined in default.h
 */

#include <cstdlib>
#include <unistd.h>
#include <sqlite3.h>
#include <ctime>
#include <cstdio>
#include "default.h"

// Externs declared in header are here
BMA180Accelerometer * g_Accel0; //!< Left Leg Accel
BMA180Accelerometer * g_Accel1; //!< Right Leg Accel
gnublin_gpio gpio;
Accel3d g_A3d0;
Accel3d g_A3d1;
int HallEffectSensorVal;       //!< The current value of the hall sensor
int initHallEffectSensorVal;   //!< The initial value of the hall sensor
bool isRunning;                //!< Is the board currently listening for data
time_t rawtime;
// File scope global variables
//static sqlite3 *db;

// FWD Declarations of functions used in this file and declared later.


#include <iostream>
// inits the program
int init()
{
	using namespace std;	

	isRunning = true;
	
    // init the pins for use
    gpio.pinMode(PIN_ON_OFF_SW, "INPUT");
    gpio.pinMode(PIN_RUNNING_LED, "OUTPUT");
    gpio.pinMode(PIN_WARN_LED, "OUTPUT");
    
    gpio.digitalWrite(PIN_RUNNING_LED, HIGH);
    gpio.digitalWrite(PIN_WARN_LED, LOW);
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
	/*if(gpio.digitalRead(PIN_ON_OFF_SW)){
            isRunning = true;
            gpio.digitalWrite(PIN_RUNNING_LED, HIGH);
    }else{
            isRunning = false;
            gpio.digitalWrite(PIN_RUNNING_LED, LOW);
    }*/

    // Update the data
	updateAccel3d(g_Accel0, &g_A3d0); // update left leg
	//updateAccel3d(g_Accel1, &g_A3d1); // update right leg
	/// \todo add a magnetic check
	
	// TEST the values to make sure there within the acceptable range
	bool accelsOk = testAccel3ds(&g_A3d0, &g_A3d1);
	bool distsOk = testHallEffectSensor();			

	// Output the data	
	if(isRunning == true){
        time(&rawtime);
        std::cout << "[" << rawtime << "]\t"
                  << g_A3d0.m_roll  << "\t" 
                  << g_A3d0.m_pitch << "\t"
	              << g_A3d0.m_xAcc  << "\t" 
                  << g_A3d0.m_yAcc  << "\t" 
                  << g_A3d0.m_zAcc << std::endl;
        if((accelsOk) | (distsOk)){
            // This is not good, tell the user about it
            gpio.digitalWrite(PIN_WARN_LED, HIGH);
        }else{
            gpio.digitalWrite(PIN_WARN_LED, LOW);
        }
    }

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

}
// updates hall effect sensor
void updateHallEffectSensor()
{

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
    if((aLeft->m_yAcc > aLeft->m_xAcc) && (aLeft->m_xAcc > 0)){
        return false;
    }
    if((aRight->m_yAcc > aRight->m_xAcc) && (aRight->m_xAcc > 0)){
        return false;
    }
	return false; // all is right in the world
}
