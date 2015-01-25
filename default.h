/** @file default.h
 * @author Henry J Schmale
 * @date January 25, 2015
 * Contains everything needed for this program
 */

#define BOARD BEAGLEBONE_BLACK
#include "gnublin.h"

#include <iostream>

// ========================================
// =========== Global Constants ===========
// ========================================

/** \brief Buzzer GPIO
 * \note Locatation: P8_3
 */
const int PIN_BUZZER = 38;

/** \brief Calibrate button GPIO
 * \note Location: P8_4
 */
const int PIN_CALIBRATE = 39;

/** \brief Calibration LED GPIO
 * \note Location: P8_5
 *
 * The pin with the calibration LED.
 * This pin goes high when in calibration mode
 */
const int PIN_CALIB_LED = 34;

/** \brief The warning LED GPIO
 * \note Location: P8_6
 *
 * This gpio goes high when the warning state is
 * met.
 */
const int PIN_WARN_LED = 35;

/** \brief The stop light
 * \note Location: P8_7
 */
const int PIN_STOP_LED = 66;

// ========================================
// ============ Global Externs ============
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


// =======================================
// ========= Function Prototypes =========
// =======================================

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
