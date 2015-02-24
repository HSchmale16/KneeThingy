/** @file default.h
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains everything needed for this program
 */

#include <iostream>                        // for basic I/O opps
#include <string>                          // for std::string
//#include <glog/logging.h>
#include "include/BMA180Accelerometer.h"
#include "include/gnublin.h"

// ========================================
// =========== Global Constants ===========
// ========================================

// ------------- Std Constant -------------
// Misc. Constants
/** \brief Wait Period in microseconds for updates
 */
const int UPDATE_WAIT_T = 50000;

/** \brief database file path
 */
const std::string DB_FILE_PATH = "./kneething.db";

/** \brief directory where logs are stored
 */
const std::string LOG_FILE_DIR = "./logs";

// ------------- Pin Constant -------------
// What pin is each thingy on.

/** \brief Buzzer GPIO
 * \note Locatation: P8_3
 * \note State: OUTPUT
 */
const int PIN_BUZZER = 69;

/** \brief Calibrate button GPIO
 * \note Location: P8_4
 * \note State: INPUT
 */
const int PIN_ON_OFF_SW = 68;

/** \brief Calibration LED GPIO
 * \note Location: P8_5
 * \note State: OUTPUT
 */
const int PIN_CALIB_LED = 34;

/** \brief Calibration Complete LED GPIO
 * \note Location: P8_6
 * \note State: OUTPUT
 */
const int PIN_CALIB_DONE_LED = 44;

/** \brief The warning LED GPIO
 * \note Location: P8_7
 * \note State: OUTPUT
 */
const int PIN_WARN_LED = 66;

/** \brief The stop light
 * \note Location: P8_8
 * \note State: OUTPUT
 */
const int PIN_STOP_LED = 67;

// ----------- i2c bus constant -----------
const int ACC0_I2C_BUS = 1;     //!< i2c bus that Accel0 runs on

const int ACC1_I2C_BUS = 1;     //!< i2c bus that Accel1 runs on

const int ACC0_I2C_ADDY = 0x38; //!< Address on i2c bus of Accel0

const int ACC1_I2C_ADDY = 0x38; //!< Address on i2c bus of Accel1


// ========================================
// ============= Structs Defs =============
// ========================================

/** \brief A struct to contain the status of an accelerometer 
 * and the starting state of that accelerometer
 */
struct Accel3d
{
	float m_roll;      //!< The roll of that accelerometer
	float m_pitch;     //!< The pitch of that accelerometer
	float m_initRoll;  //!< The initial roll
	float m_initPitch; //!< The initial pitch
	int m_xAcc;        //!< The acceleration on the x-axis
	int m_yAcc;        //!< The acceleration on the y-axis
	int m_zAcc;        //!< The acceleration on the z-axis
	int m_initX;       //!< Initial Acceleration on the x-axis
	int m_initY;
	int m_initZ;	
	// default ctor - init all to 0
	Accel3d()
	{
		m_roll = 0;
		m_pitch = 0;
		m_initRoll = 0;
		m_initPitch = 0;
		m_xAcc = 0;
		m_yAcc = 0;
		m_zAcc = 0;
		m_initX = 0;
		m_initY = 0;
		m_initZ = 0;
	}
};
// ========================================
// ========= Function Prototypes ==========
// ========================================

/** \brief Initializes the system
 * \return 0 on success, anything else on fail
 */
int init();

/** \brief Runs the event loop
 * \return 0 on successful exit
 * \note this function should be called many times
 * inside a loop that waits for this function
 * to return anything that is NOT 0.
 */
int eventLoop();

/** \brief Inits the hall effect sensor
 *
 * This function sets the initial value of the hall effect
 * sensor for use in acceptable/unacceptable tests.
 */
void initHallEffectSensor();


/** \brief updates the Hall effect sensor value
 */
void updateHallEffectSensor();

/** \brief test to make sure the hall effect sensor is within the
 * acceptable range.
 * \return false if the values are in the acceptable range
 * False ===> It's all good.
 * True  ===> BAD
 * \todo Ask potter to explain the hall effect sensor, and how
 * it scales with distance.
 */
bool testHallEffectSensor();

/** \brief updates an accel3d  struct
 * \param accel an accelerometer instance to read from
 * \param a3d the struct to update
 * \return Nothing
 */
void updateAccel3d(BMA180Accelerometer *accel,
				Accel3d *a3d);

/** \brief initializes an accel3d struct based off an accelerometer
 * readings at that moment.
 * \param accel The accelerometer to read for initialization.
 * \baram a3d The struct to initialize. 
 */
void initAccel3d(BMA180Accelerometer *accel,
				Accel3d *a3d);

/** \brief Performs a check on the accelerometer to see
 * if an error condition exists.
 * \param aLeft Accelerometer on the left leg.
 * \param aRight Accelerometer on the right leg.
 * \return false if in acceptable range, otherwise true.
 * False ===> Good
 * True  ===> Bad
 */
bool testAccel3ds(Accel3d *aLeft, Accel3d *aRight);


// ========================================
// ============ Global Externals ==========
// ========================================

/** \brief GPIO Object */
extern gnublin_gpio gpio;

/** \brief Accelerometer on the left leg
 */
extern BMA180Accelerometer * g_Accel0;

/** \brief Accelerometer on the right leg
 */
extern BMA180Accelerometer * g_Accel1;

/** \brief Accelerometer structs to hold the data recieved from each
 * Accelerometer.
 *
 * This one goes to g_Accel0.
 */
extern Accel3d g_A3d0;

/** \brief Accelerometer struct
 *
 * This one goes to g_Accel1;
 */
extern Accel3d g_A3d1;

/** \brief The current output of the hall effect sensor.
 */
extern int HallEffectSensorVal;




