#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <wiringPi.h>
#include <wiringSerial.h>
//#include <softPwm.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

/*int main(void)
{
	char buf[6];
	char tty[] = "/dev/ttyAMA0";
	int serial;
	
	gpioInitialise();
	//gpioTerminate();

	serial = serOpen(tty, 19200, 0);
	int isReceved = 0;
	while(1){
		isReceved = serRead(serial, buf, 5);
		if(isReceved>1){
			printf("%s\n", buf);
		}
		/*
		if(cv::waitKey(1) > 0){
			break;
		}
		buf[6] = 0;
	}
	serClose(serial);
	return(0);
}*/

int main(){

	/* シリアルポートオープン */
	int fd = serialOpen("/dev/ttyAMA0",19200);
	if(fd<0){
		printf("can not open serialport");
	}
	double start_time = time_time();
	double now_time, now_time2;
	while(1){
		/* 受信処理 */
		while(serialDataAvail(fd)){
			start_time = time_time();
			printf("%c\n" , serialGetchar(fd) );
			fflush(stdout);
			now_time = time_time();
			printf("%f\n", (now_time - start_time));
		}

		/* 送信処理 */
		//serialPuts(fd,"hello world\n");

		//delay(1000);
	}

	return 0;
}

