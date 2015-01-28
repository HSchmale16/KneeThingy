/** \author Henry J Schmale
 * \date January 25, 2015
 *
 * \mainpage Knee Thing
 * \section Potter's Group should write a description of program here.
 */

// this file contains everything needed to work with gnublin and run this program
// it has the function prototypes and the various constants defined in it
#include "default.h"

int main(int argc, char ** argv)
{
	int rc = init(); // return code
	if(rc != 0)
	{
		// Error Handing, init should return 0
		return rc;
	}
	// begin event loop
	while(rc == 0) // if rc != 0 something bad happened
	{
		rc = eventLoop();
	}
	return rc;
}
