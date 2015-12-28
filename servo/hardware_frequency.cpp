#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <iostream>

int main(int argc, char* argv[]) {
	//pwm initialize
	//gpioCfgClock(1, 0, 100);
	if(gpioInitialise() < 0) return -1;
	//pigpio CW/CCW pin setup
	//X:18, Y1:7, Y2:12
	//gpioSetMode(18, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	//gpioSetMode(25, PI_OUTPUT);
	//limit-switch setup

	std::cout << "Hardware Frequency" << std::endl;
	gpioHardwarePWM(18, 0, 500000);
	gpioHardwarePWM(13, 0, 500000);
	gpioHardwarePWM(18, 670, 500000);
	
	/*std::cout << "Play Sound!!" <<std::endl;
	system("sudo mpg321 -q -l0 ../pr-equipment/Hardware/hisyo.mp3 &");*/
	
	int num;
	std::cin >> num;
	
	gpioHardwarePWM(18, 0, 500000);

	gpioTerminate();

	return 0;
}

//mpg321 -q -l0 ../pr-equipment/Hardware/hisyo.mp3 &
//sudo mpg321 -q -l0 ../pr-equipment/Hardware/hisyo.mp3 &

