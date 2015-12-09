#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>

/* シグナル受信/処理 */
void signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	gpioTerminate();
	exit(0);
}

int main(int argc, char* argv[]) {
	//pwm initialize
	//gpioCfgClock(4, 0, 100);
	if (gpioInitialise() < 0) {
		std::cout << "pigpio initialisation failed." << std::endl;
	} else {
		std::cout << "pigpio initialised okay." << std::endl;
	}

	/*if (signal(SIGINT, &signalHandler) == SIG_ERR) {
		std::cout << "I could not set up signal. finished" << std::endl;
		gpioTerminate();
		exit(1);
	}*/
	
	char sertty[] = "/dev/ttyAMA0";
	int handle = serOpen(sertty, 19200, 0);
	
	if(handle>=0){
		std::cout << "OK, serial port open" << std::endl;
	}
	else{
		std::cout << "NG, serial port cannnot open" << std::endl;
	}
	
	char input[5];
	double start_time;
	double now_time, passed_time;
	int frequency = 0;
	while(1){
		while(serDataAvailable(handle)){
			start_time = time_time();
			serRead(handle, input, 5);
			std::cout << input << std::endl;
			now_time = time_time();
			std::cout << now_time - start_time << std::endl;
		}
	}
	
	serClose(handle);
	gpioTerminate();

	return 0;
}

