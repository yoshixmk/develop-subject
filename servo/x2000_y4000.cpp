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
	
	while(1){
		//X
		gpioPWM(25, 128);
		gpioSetPWMfrequency(25, 2000);
		//Y1
		gpioPWM(23, 128);
		gpioSetPWMfrequency(23, 4000);
		//gpioSetPWMfrequency(23, 40000);
		//Y2
		gpioPWM(24, 128);
		gpioSetPWMfrequency(24, 4000);
		//gpioSetPWMfrequency(24, 40000);
		getline(cin, input_line);
		cout << input_line << endl;
		break;
	}

	gpioTerminate();

	return 0;
}
