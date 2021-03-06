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

	if (signal(SIGINT, &signalHandler) == SIG_ERR) {
	}
	
	//pigpio CW/CCW pin setup
	//X:18, Y1:14, Y2:15
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(7, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(19, PI_OUTPUT);
	gpioSetMode(12, PI_OUTPUT);
	
	gpioWrite(6, 0);
	
	int f = gpioHardwarePWM(18, 0, 500000); 
	
	char sertty[] = "/dev/ttyAMA0";
	int handle = serOpen(sertty, 19200, 0);
	
	if(handle>=0){
		std::cout << "OK, serial port open" << std::endl;
	}
	else{
		std::cout << "NG, serial port cannnot open" << std::endl;
	}
	
	char input[2];
	double start_time;
	double now_time, passed_time;
	int frequencyX = 0;
	int frequencyY = 0;
	int preFrequencyX = 0;
	int preFrequencyY = 0;
	int isRead = 0;
	while(1){
		start_time = time_time();
		while(serDataAvailable(handle)){
			start_time = time_time();
			isRead = serRead(handle, input, 2);
			//暗黙のint変換。char->unsigned char->int
			//0~255 -> 0~2550Hz とするための、10倍
			if(isRead >= 0){
				frequencyX = (unsigned char)input[0] * 10 * 2;
				frequencyY = (unsigned char)input[1] * 10 * 2;
				std::cout << "X: " << frequencyX << std::endl;
				std::cout << "Y: " << frequencyY << std::endl;
				
				if(frequencyX != preFrequencyX){
					f = gpioHardwarePWM(18, frequencyX, 500000);
					preFrequencyX = frequencyX;
				}
				isRead = 0;
			}
			
			now_time = time_time();
			std::cout << now_time - start_time << std::endl;
		}
	}
	
	serClose(handle);
	gpioTerminate();

	return 0;
}

