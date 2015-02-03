#ifndef SQL_CALLBACKS_H
#define SQL_CALLBACKS_H

/** @file sqlCallbacks.h
 * @author Henry J Schmale
 * @date 27 January 2015
 * 
 * This file contains the fwd declarations for sql callbacks that are
 * defined in sqlCallbacks.cpp
 * All callbacks are prefixed with a `cb_`
 */

// #include <sqlite3.h> // might as well as this is callbacks for sqlite3

/** \brief an empty callback
 */
int cb_Empty(void *data, int argc, char ** argv,
            char ** azColName){ };

// More callbacks to be added. Yay!

#endif
