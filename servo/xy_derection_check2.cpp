#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>
using namespace std;


/* シグナル受信/処理 */
void signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	gpioTerminate();
	exit(0);
}

int main(int argc, char* argv[]) {
	//pwm initialize
	//gpioCfgClock(4, 0, 100);
	//pwm initialize
	//gpioCfgClock(1, 0, 100);
	if (gpioInitialise() < 0) {
		std::cout << "pigpio initialisation failed." << std::endl;
	} else {
		std::cout << "pigpio initialised okay." << std::endl;
	}

	if (signal(SIGINT, &signalHandler) == SIG_ERR) {
		std::cout << "I could not set up signal. finished" << std::endl;
		gpioTerminate();
		exit(1);
	}
	//pigpio CW/CCW pin setup
	//X:18, Y1:14, Y2:15
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(7, PI_OUTPUT);
	gpioSetMode(12, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	
	int lr = 1;
	gpioWrite(25, lr);//18
	string input_line;
	double start = time_time();
	//int f = gpioSetPWMfrequency(25, 320);
	int f = gpioHardwarePWM(18, 0, 500000); 
	gpioSetPWMfrequency(23, 1000);
	gpioSetPWMfrequency(24, 1000);
	int frequency_changing = 0;
	double now_time, passed_time;
	int i=100;
	int j=0;
	while(1){
		std::cout << "Robot Speed:" << f << std::endl;
		if(i < 500000){
			if(j==3){
				i++;
				j = 0;
				if(i%100 == 0){
					if((i/100+1)*100 < 2600){
						f = gpioHardwarePWM(18, ((i/100)+1)*100, 500000);
					}
				}
			}
			else{
				j++;
			}
		}
		
		//f = gpioHardwarePWM(18, ((i/100)+1)*100, ((i/100)+1)*100/2); 
		
		
				//X
				/*now_time = time_time();
				passed_time = now_time - start;
				if(passed_time < 0.1){
					if(frequency_changing==0){
						gpioWrite(25, lr);//18
						f = gpioHardwarePWM(25, 600, 512);
						frequency_changing++;
					}
				}
				else if(passed_time < 0.2){
					if(frequency_changing==1){
						std::cout << "YA-HA-!!" << std::endl;
						//f = gpioSetPWMfrequency(25, 500);
						gpioWrite(25, lr);
						f = gpioHardwarePWM(18, 800, 512);
						frequency_changing++;
					}
				}
				else if(passed_time < 0.3){
					if(frequency_changing==2){
						//f = gpioSetPWMfrequency(25, 800);
						gpioWrite(25, lr);
						f = gpioHardwarePWM(18, 1000, 512);
						frequency_changing++;
					}
				}*/
				/*else if(passed_time < 0.4){
					if(frequency_changing==3){
						f = gpioSetPWMfrequency(25, 1000);
						gpioWrite(18, lr);
						gpioPWM(25, 128);
						frequency_changing++;
					}
				}
				else if(passed_time < 1.9){
					if(frequency_changing==4){
						f = gpioSetPWMfrequency(25, 1600);
						gpioWrite(18, lr);
						gpioPWM(25, 128);
						frequency_changing++;
					}
				}*/
				
				//Y1
				//gpioWrite(7, 0);
				//gpioPWM(23, 128);
				//Y2
				//gpioWrite(12, 1);
				//gpioPWM(24, 128);
	}

	gpioTerminate();

	return 0;
}
