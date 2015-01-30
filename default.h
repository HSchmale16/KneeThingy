/** @file default.h
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains everything needed for this program
 */

#define BOARD BEAGLEBONE_BLACK
#include "include/gnublin.h"               // Accessing GPIO + Analog reads

#include <iostream>                        // for basic I/O opps
#include <string>                          // for std::string
#include "include/BMA180Accelerometer.h"

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
const int PIN_CALIB_BUTTON = 68;

/** \brief Calibration LED GPIO
 * \note Location: P8_5
 * \note State: OUTPUT
 */
const int PIN_CALIB_LED = 45;

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



// ========================================
// ============= Structs Defs =============
// ========================================

/** \brief A struct to contain the status of an accelerometer 
 * and the starting state of that accelerometer
 */
struct Accel3d
{
	float m_fRoll;      //!< The roll of that accelerometer
	float m_fPitch;     //!< The pitch of that accelerometer
	float m_fInitRoll;  //!< The initial roll
	float m_fInitPitch; //!< The initial pitch
	int m_xAcc;       //!< The acceleration on the x-axis
	int m_yAcc;       //!< The acceleration on the y-axis
	int m_zAcc;       //!< The acceleration on the z-axis
	int m_initX;      //!< Initial Acceleration on the x-axis
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
 * \return 0 if all is right, 1 if the user is messing up.
 */
bool testAccel3ds(Accel3d *aLeft, Accel3d *aRight);

// ========================================
// ============ Global Externals ==========
// ========================================

/** \brief The GPIO object, required to access GPIO on the beagle bone
 * black.
 *
 * It allows access to the the GPIO headers for digitial I/O on the
 * GPIO pins.
 */
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


