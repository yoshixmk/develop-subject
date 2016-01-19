#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>
#include <termios.h>

int handle;

/* シグナル受信/処理 */
void signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	serClose(handle);
	gpioTerminate();
	exit(0);
}

void gpioUSleep(void){
	usleep(1);
}

void sigcatch(int sig){
	int closest_frequency;
	
	printf("catch signal \n",sig);
	closest_frequency = gpioHardwarePWM(18, 0,500000);
	closest_frequency = gpioHardwarePWM(19, 0,500000);
	closest_frequency = gpioHardwarePWM(13, 0,500000);
	exit(1);
}

int main(int argc, char* argv[]) {
	//pwm initialize
	//gpioCfgClock(4, 0, 100);
	
	if(SIG_ERR == signal(SIGINT,sigcatch)){	//プログラム終了時にモータを止める
		printf("fail");
		exit(1);
	}
	
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
	gpioSetMode(13, PI_OUTPUT);
	
	gpioWrite(6, 0);
	
	int f = gpioHardwarePWM(18, 0, 500000); 
	
	/*struct termios options;
	int fd;
	tcgetattr(fd, &options);
	options.c_cflag |= CS8;//8bit 
	options.c_iflag |= IXOFF;
	tcsetattr(fd, TCSANOW, &options);*/
	char sertty[] = "/dev/ttyAMA0";
	handle = serOpen(sertty, 115200, 0);
	
	if(handle>=0){
		std::cout << "OK, serial port open" << std::endl;
	}
	else{
		std::cout << "NG, serial port cannnot open" << std::endl;
	}
	
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
		start_time = time_time();

		while(serDataAvailable(handle)){
			start_time = time_time();
			isRead = serRead(handle, input, 4);
			//暗黙のint変換。char->unsigned char->int
			//0~255 -> 0~2550Hz とするための、10倍
			if(isRead >= 0){
				frequencyX = (unsigned char)input[0] * 10 * 2;
				frequencyY = (unsigned char)input[1] * 10 * 2;
				direction  = (unsigned char)input[2];
				std::cout << "X: " << frequencyX << std::endl;
				std::cout << "Y: " << frequencyY << std::endl;
				std::cout << "DIST: " << direction << std::endl;
				std::cout << std::flush;
				
				if(direction != predirection){
					if(direction  == 'A'){	
						gpioWrite(25, 1);	//X
						gpioWrite(7, 0);	//Y前
						gpioWrite(24, 1);
						//printf("AAA\n");
					}
					else if(direction  == 'B'){	
						gpioWrite(25, 0);
						gpioWrite(7, 0);	//前
						gpioWrite(24, 1);
						//printf("BBB\n");
					}
					else if(direction  == 'C'){	
						gpioWrite(25, 0);
						gpioWrite(7, 1);	//後
						gpioWrite(24, 0);
						//printf("CCC\n");
					}
					else if(direction  == 'D'){	
						gpioWrite(25, 1);
						gpioWrite(7, 1);	//後
						gpioWrite(24, 0);
						//printf("DDD\n");
					}
					
					
					predirection = direction;
				}
				

				if(frequencyY != preFrequencyY){
					
					f = gpioHardwarePWM(19, frequencyY, 500000);
					f = gpioHardwarePWM(13, frequencyY, 500000);
					preFrequencyY = frequencyY;
				}
				
				else if(frequencyX != preFrequencyX){
					f = gpioHardwarePWM(18, frequencyX, 500000);
					preFrequencyX = frequencyX;
				}
				
				isRead = 0;
			}
			now_time = time_time();
			std::cout << now_time - start_time << std::endl;
			if(frequencyX == 5100){
				break;
			}
		}
		gpioUSleep();
		//std::cout << std::flush;
		if(frequencyX == 5100){
			break;
		}
	}
	
	serClose(handle);
	gpioTerminate();

	return 0;
}

