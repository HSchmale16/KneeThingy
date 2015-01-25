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



// ========================================
// ============ Global Externs ============
// ========================================

/** \brief GPIO Global
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
 * \note this function should be called many times inside a loop that waits for this function
 * anything that is not 0.
 */
int eventLoop();
