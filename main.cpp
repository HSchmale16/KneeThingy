/** \author Henry J Schmale
 * \date January 25, 2015
 *
 * \mainpage Knee Thing
 * \section Potter's Group should write a description of program here.
 */

// this file contains everything needed to work with gnublin
// and run this program it has the function prototypes and 
// the various constants defined in it
#include "default.h"
#include <csignal> // For Handling Interupts

void sigcb_SIGINT(int signum){
    std::cout << "Recived Signal: " << signum << std::endl;
    std::cout << "Turn off LEDS" << std::endl;
    gpio.digitalWrite(PIN_RUNNING_LED, LOW);
    gpio.digitalWrite(PIN_WARN_LED, LOW);
    std::cout << "Unexport pins" << std::endl;
    gpio.unexport(PIN_ON_OFF_SW);
    gpio.unexport(PIN_RUNNING_LED);
    gpio.unexport(PIN_WARN_LED);
    std::cout << "Finished shutdown" << std::endl;
    exit(signum);
}

int main(int argc, char ** argv)
{
    signal(SIGINT, sigcb_SIGINT);
	// initiate logging first
	//FLAGS_log_dir = "./logs/";
	//google::InitGoogleLogging(argv[0]);
	//LOG(INFO) << "Initialized google logging";	
	
	// now run the primary init
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
