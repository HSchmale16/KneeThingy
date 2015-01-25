// this file contains everything needed to work with gnublin and run this program
// it has the function prototypes and the various constants defined in it
#include "default.h"

// Declare Variables
gnublin_gpio gpio;
gnublin_i2c accel0;
gnublin_i2c accel1;

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
