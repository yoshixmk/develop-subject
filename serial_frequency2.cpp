#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>
#include <termios.h>


int main(int argc, char* argv[]) {

	if (gpioInitialise() < 0) {
		std::cout << "pigpio initialisation failed." << std::endl;
	} else {
		std::cout << "pigpio initialised okay." << std::endl;
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
	
	char input[] = {0};
	double start_time;
	double now_time, passed_time;
	char direction = '\0';
	char predirection = '\0';
	int frequencyX = 0;
	int frequencyY = 0;
	int preFrequencyX = 0;
	int preFrequencyY = 0;
	//char distination;
	int isRead = 0;
	int i;
	
	
	while(1){
		printf("nyuuryoku:\n");
		scanf("%c",&direction);
		if(direction != predirection){
			if(direction  == 'A'){	
				gpioWrite(25, 1);
				gpioWrite(7, 0);	//前
				gpioWrite(24, 1);
				printf("AAA\n");
			}
			else if(direction  == 'B'){	
				gpioWrite(25, 0);
				gpioWrite(7, 0);	//前
				gpioWrite(24, 1);
				printf("BBB\n");
			}
			else if(direction  == 'C'){	
				gpioWrite(25, 0);
				gpioWrite(7, 1);	//後
				gpioWrite(24, 0);
				printf("CCC\n");
			}
			else if(direction  == 'D'){	
				gpioWrite(25, 1);
				gpioWrite(7, 1);	//後
				gpioWrite(24, 0);
				printf("DDD\n");
			}
			f = gpioHardwarePWM(18, 500, 500000);
			f = gpioHardwarePWM(19, 500, 500000);
			f = gpioHardwarePWM(12, 500, 500000);
			sleep(1);
			f = gpioHardwarePWM(18, 0, 500000);
			f = gpioHardwarePWM(19, 0, 500000);
			f = gpioHardwarePWM(12, 0, 500000);
			predirection = direction;
		}
	}


	return 0;
}

