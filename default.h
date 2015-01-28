/** @file default.h
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains everything needed for this program
 */

#define BOARD BEAGLEBONE_BLACK
#include "gnublin.h"

#include <iostream>                        // for basic I/O opps
#include <string>                          // for std::string
#include "include/BMA180Accelerometer.h"

// ========================================
// =========== Global Constants ===========
// ========================================

// ------------- Std Constant -------------
// Misc. Constants

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
const int PIN_BUZZER = 38;

/** \brief Calibrate button GPIO
 * \note Location: P8_4
 * \note State: INPUT
 */
const int PIN_CALIB_BUTTON = 39;

/** \brief Calibration LED GPIO
 * \note Location: P8_5
 * \note State: OUTPUT
 */
const int PIN_CALIB_LED = 34;

/** \brief Calibration Complete LED GPIO
 * \note Location: P8_6
 * \note State: OUTPUT
 */
const int PIN_CALIB_DONE_LED = 35;

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

/** \brief An Accelerometer struct that holds the current state of a
 * single accelerometer.
 */
struct Accelerometer
{
	int m_rot;     //!< The current rotation of that accelerometer.
	int m_initRot; //!< The init rotation of this. Set during calibration.
};

/** \brief A 3d Accelerometer struct. This is a wrapper around a regular
 * accelerometer to allow for usage in 3 dimensions.
 */
struct Accelerometer3d
{
	Accelerometer m_xAcc; //!< x-axis Accelerometer
	Accelerometer m_yAcc; //!< y-axis Accelerometer
	Accelerometer m_zAcc; //!< z-axis Accelerometer
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
 * to return anything that is _NOT_ 0.
 */
int eventLoop();

// ========================================
// ============ Global Externals ==========
// ========================================
extern gnublin_gpio gpio;
extern BMA180Accelerometer * g_Accel0; // Accel on the left leg
extern BMA180Accelerometer * g_Accel1; // Accel on the right leg
