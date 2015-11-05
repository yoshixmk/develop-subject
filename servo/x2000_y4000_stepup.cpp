#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>
using namespace std;

int main(int argc, char* argv[]) {
	//pwm initialize
	gpioCfgClock(4, 0, 100);
	//pwm initialize
	//gpioCfgClock(1, 0, 100);
	if(gpioInitialise() < 0) return -1;
	//pigpio CW/CCW pin setup
	//X:18, Y1:14, Y2:15
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(14, PI_OUTPUT);
	gpioSetMode(15, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//limit-switch setup
	gpioSetMode(5, PI_INPUT);
	gpioWrite(5, 0);
	gpioSetMode(6, PI_INPUT);
	gpioWrite(6, 0);
	gpioSetMode(7, PI_INPUT);
	gpioWrite(7, 0);
	gpioSetMode(8, PI_INPUT);
	gpioWrite(8, 0);
	gpioSetMode(13, PI_INPUT);
	gpioSetMode(19, PI_INPUT);
	gpioSetMode(26, PI_INPUT);
	gpioSetMode(21, PI_INPUT);

	string input_line;
	clock_t start = clock();
	int f = gpioSetPWMfrequency(25, 1600);
	gpioSetPWMfrequency(23, 2000);
	gpioSetPWMfrequency(24, 2000);
	int frequency_changing = 0;
	while(1){
		std::cout << "Robot Speed:" << f << std::endl;

		/*clock_t end = clock();
		if((double)(end - start)/CLOCKS_PER_SEC < 1.0){
			//X
			gpioWrite(18, 1);
			gpioPWM(25, 128);
		}
		else{
			if(frequency_changing == 0){
				f = gpioSetPWMfrequency(25, 4000);
				frequency_changing++;
			}
			gpioWrite(18, 1);
			gpioPWM(25, 128);
		}*/
		clock_t end = clock();
		if((double)(end - start)/CLOCKS_PER_SEC < 0.01){
			//X
			gpioWrite(18, 1);
			if(frequency_changing == 0){
				f =gpioSetPWMfrequency(25, 1000);
				gpioPWM(25, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.03){
			//X
			if(frequency_changing == 1){
				f =gpioSetPWMfrequency(25, 1250);
				gpioPWM(25, 128);
				frequency_changing++;
			}
			//Y1
			gpioWrite(14, 0);
			gpioPWM(23, 128);
			//Y2
			gpioWrite(15, 1);
			gpioPWM(24, 128);
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.05){
			//X
			if(frequency_changing == 2){
				f =gpioSetPWMfrequency(25, 2000);
				gpioPWM(25, 128);
				frequency_changing++;
			}
			//Y1
			gpioWrite(14, 0);
			gpioPWM(23, 128);
			//Y2
			gpioWrite(15, 1);
			gpioPWM(24, 128);
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.1){
				//X
				if(frequency_changing == 3){
					f =gpioSetPWMfrequency(25, 2500);
					gpioPWM(25, 128);
					frequency_changing++;
				}
				//Y1
				gpioWrite(14, 0);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(15, 1);
				gpioPWM(24, 128);
			}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.3){
			//X
			gpioPWM(25,0);
			//Y1
			gpioPWM(23, 0);
			//Y2
			gpioPWM(24, 0);
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.35){
			//X
			gpioWrite(18, 0);
			if(frequency_changing == 4){
				f =gpioSetPWMfrequency(25, 1000);
				gpioPWM(25, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.4){
			//X
			if(frequency_changing == 5){
				f =gpioSetPWMfrequency(25, 1250);
				gpioPWM(25, 128);
				frequency_changing++;
			}
			//Y1
			gpioWrite(14, 1);
			gpioPWM(23, 128);
			//Y2
			gpioWrite(15, 0);
			gpioPWM(24, 128);
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.5){
			//X
			if(frequency_changing == 6){
				f =gpioSetPWMfrequency(25, 2000);
				gpioPWM(25, 128);
				frequency_changing++;
			}
			//Y1
			gpioWrite(14, 1);
			gpioPWM(23, 128);
			//Y2
			gpioWrite(15, 0);
			gpioPWM(24, 128);
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.6 ){
			//X
			gpioWrite(18, 0);
			gpioPWM(25,0);
			//Y1
			gpioPWM(23, 0);
			//Y2
			gpioPWM(24, 0);
		}
		else{
			start = clock();
			frequency_changing = 0;
		}
	}

	gpioTerminate();

	return 0;
}
