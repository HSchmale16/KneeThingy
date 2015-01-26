/** @file default.h
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains everything needed for this program
 */

#define BOARD BEAGLEBONE_BLACK
#include "gnublin.h"

#include <iostream> // for basic I/O opps
#include <string>   // for std::string

// ========================================
// =========== Global Constants ===========
// ========================================

// ------------- Pin Constant -------------
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
const int PIN_DONE_CALIB_LED = 35;

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

/** \brief Address of Accel0 on I2C bus
 * \note this needs to be found from the spec sheet.
 */
const int ACCEL0_I2C_ADDR = 0x26;

/** \brief Address of Accel1 on I2C bus
 * \note this needs to be found from the spec sheet.
 */
const int ACCEL1_I2C_ADDR = 0x26;

// ========================================
// ============ Global Externals ==========
// ========================================

/** \brief GPIO Object Global
 */
extern gnublin_gpio gpio;

/** \brief accel0 - the accelerometer on the left leg
 */
extern gnublin_i2c accel0;

/** \brief accel1 - the accelerometer on the right leg
 */
extern gnublin_i2c accel1;


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
