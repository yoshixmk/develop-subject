#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <wiringPi.h>

int main(int argc, char* argv[]) {
    printf("motor stop!\n");
    if(gpioInitialise() < 0) return -1;
	gpioTerminate();

    return 0;
}

