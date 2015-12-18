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
	//X:18, Y1:7, Y2:12
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(127, PI_OUTPUT);
	gpioSetMode(12, PI_OUTPUT);
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
	int f = gpioSetPWMfrequency(25, 1000);
	gpioSetPWMfrequency(23, 1000);
	gpioSetPWMfrequency(24, 1000);
	int frequency_changing = 0;
	while(1){
		std::cout << "Robot Speed:" << f << std::endl;

		gpioPWM(25, 0);
		

		clock_t end = clock();
		if((double)(end - start)/CLOCKS_PER_SEC < 0.01){
			//X
			if(frequency_changing == 0){
				gpioWrite(18, 1);
				f =gpioSetPWMfrequency(25, 1000);
				gpioSetPWMfrequency(23, 1000);
				gpioSetPWMfrequency(24, 1000);
				//X
				gpioWrite(18, 1);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 0);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 1);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.03){
			//X
			if(frequency_changing == 1){
				f =gpioSetPWMfrequency(25, 1250);
				gpioSetPWMfrequency(23, 1250);
				gpioSetPWMfrequency(24, 1250);
				//X
				gpioWrite(18, 1);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 0);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 1);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.05){
			//X
			if(frequency_changing == 2){
				f =gpioSetPWMfrequency(25, 2000);
				gpioSetPWMfrequency(23, 2000);
				gpioSetPWMfrequency(24, 2000);
				//X
				gpioWrite(18, 1);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 0);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 1);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.08){
			if(frequency_changing == 3){
				//X
				f =gpioSetPWMfrequency(25, 2500);
				gpioSetPWMfrequency(23, 2500);
				gpioSetPWMfrequency(24, 2500);
				//X
				gpioWrite(18, 1);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 0);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 1);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.3){
			if(frequency_changing == 4){
				//X
				gpioPWM(25,0);
				//Y1
				gpioPWM(23, 0);
				//Y2
				gpioPWM(24, 0);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.31){
			//X
			gpioWrite(18, 0);
			if(frequency_changing == 5){
				f =gpioSetPWMfrequency(25, 1000);
				gpioSetPWMfrequency(23, 1000);
				gpioSetPWMfrequency(24, 1000);
				//X
				gpioWrite(18, 0);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 1);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 0);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.33){
			//X
			if(frequency_changing == 6){
				f =gpioSetPWMfrequency(25, 1250);
				gpioSetPWMfrequency(23, 1250);
				gpioSetPWMfrequency(24, 1250);
				//X
				gpioWrite(18, 0);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 1);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 0);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 0.35){
			//X
			if(frequency_changing == 7){
				f =gpioSetPWMfrequency(25, 2000);
				gpioSetPWMfrequency(23, 2000);
				gpioSetPWMfrequency(24, 2000);
				//X
				gpioWrite(18, 0);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 1);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 0);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 3.0){//0.38
			//X
			if(frequency_changing == 8){
				f =gpioSetPWMfrequency(25, 2500);
				gpioSetPWMfrequency(23, 2500);
				gpioSetPWMfrequency(24, 2500);
				//X
				gpioWrite(18, 0);
				gpioPWM(25, 128);
				//Y1
				gpioWrite(7, 1);
				gpioPWM(23, 128);
				//Y2
				gpioWrite(12, 0);
				gpioPWM(24, 128);
				frequency_changing++;
			}
		}
		else if((double)(end - start)/CLOCKS_PER_SEC < 3.5 ){//0.5
			if(frequency_changing == 9){
				//X
				gpioWrite(18, 0);
				gpioPWM(25,0);
				//Y1
				gpioPWM(23, 0);
				//Y2
				gpioPWM(24, 0);
				frequency_changing++;
			}

		}
		else{
			start = clock();
			frequency_changing = 0;
		}
	}

	gpioTerminate();

	return 0;
}
