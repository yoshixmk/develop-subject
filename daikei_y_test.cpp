#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <sys/time.h>
#include <iostream>
#include <signal.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include "pr-equipment/Color/PerspectiveTransformation.h"
#include "pr-equipment/Hardware/Camera.h"
#include "pr-equipment/Color/HockeyTableMasking.h"

void sigcatch(int);

int main(int argc, char* argv[])
{
	//pwm initialize
	if(gpioInitialise() < 0) return -1;
	//pigpio CW/CCW pin setup
	//X:18, Y1:7, Y2:12
	gpioSetMode(18, PI_OUTPUT); 
	gpioSetMode(7, PI_OUTPUT);
	gpioSetMode(13, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(19, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//limit-switch setup
	gpioSetMode(5, PI_INPUT);
	gpioWrite(5, 0);
	//razupai conection
	gpioSetMode(8, PI_INPUT);
	
	int target_direction = -1; //目標とする向き　時計回り＝1、　反時計回り＝0

	int closest_frequency;
	int closest_frequency1;

	int freq_up=0;
	int freq_up_cnt=1;		//周波数を上げる回数
	int freq_ch=100;			//周波数切り替え
	int freq_ch2=100;
	int std_time = 250000;		//中間の間の時間

	gpioWrite(6, 1);			//ファンの出力ON
	
	target_direction =0;
	int target_direction_y1 =0;
	int target_direction_y2 =1;
	gpioWrite(25, target_direction);	//X
	gpioWrite(7, target_direction_y1);	//Y1
	gpioWrite(24, target_direction_y2);	//Y2
	
	closest_frequency1 = gpioHardwarePWM(18, 0,500000);
	closest_frequency = gpioHardwarePWM(19, 0,500000);
	closest_frequency = gpioHardwarePWM(13, 0,500000);
	
//		for(int i=0;i<10000;i++);
//		closest_frequency = gpioHardwarePWM(18, 0,500000);

	if(SIG_ERR == signal(SIGINT,sigcatch)){	//プログラム終了時にモータを止める
		printf("fail");
		exit(1);
	}
	
	int Get;
	
/*	while(1){
		closest_frequency1 = gpioHardwarePWM(18, 500,500000);
		sleep(1);
		closest_frequency1 = gpioHardwarePWM(18, 1,500000);
		sleep(1);
		Get = gpioGetPWMfrequency(18);
		printf("freq: %d\n",Get);
		target_direction =1;
		gpioWrite(25, target_direction);	//X
		sleep(1);
		closest_frequency = gpioHardwarePWM(19, 300,500000);
		closest_frequency = gpioHardwarePWM(12, 300,500000);
		Get = gpioGetPWMfrequency(18);
		printf("freq: %d\n",Get);
		sleep(1);
		closest_frequency = gpioHardwarePWM(19, 0,500000);
		closest_frequency = gpioHardwarePWM(12, 0,500000);
		Get = gpioGetPWMfrequency(18);
		printf("freq: %d\n",Get);
		target_direction_y1 =1;
		target_direction_y2 =0;
		gpioWrite(7, target_direction_y1);	//Y1（ロボから見て右）
		gpioWrite(24, target_direction_y2);	//Y2（ロボから見て左）
		sleep(1);
		closest_frequency = gpioHardwarePWM(19, 500,500000);
		closest_frequency = gpioHardwarePWM(12, 500,500000);
		Get = gpioGetPWMfrequency(18);
		printf("freq: %d\n",Get);
		sleep(1);
		closest_frequency = gpioHardwarePWM(19, 0,500000);
		closest_frequency = gpioHardwarePWM(12, 0,500000);
		Get = gpioGetPWMfrequency(18);
		printf("freq: %d\n",Get);
		target_direction_y1 =0;
		target_direction_y2 =1;
		gpioWrite(7, target_direction_y1);	//Y1
		gpioWrite(24, target_direction_y2);	//Y2
		sleep(1);

	}*/

	
	int y=2000;
	while(1){
		
		for(int i=0;i<freq_up_cnt;i++){
//			closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			Get = gpioGetPWMfrequency(18);
//			printf("freq: %d\n",Get);
			closest_frequency = gpioHardwarePWM(19, y+freq_up,500000);
			//closest_frequency = gpioHardwarePWM(13, 500+freq_up,500000);
			if(i<freq_up_cnt){
				usleep(10000);	//10ms
				freq_up=freq_up+freq_ch;
			}
			/*else{
				usleep(5000);	//10ms
				freq_up=freq_up+freq_ch2;
				closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			}*/
		}
		usleep(std_time);
		
		for(int i=0;i<=freq_up_cnt;i++){
//			closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			Get = gpioGetPWMfrequency(18);
//			printf("freq: %d\n",Get);
			closest_frequency = gpioHardwarePWM(19, y+freq_up,500000);
			//closest_frequency = gpioHardwarePWM(13, 500+freq_up,500000);
			if(i<freq_up_cnt){
				usleep(10000);	//10ms
				freq_up=freq_up-freq_ch;
			}
			/*else{
				usleep(5000);	//10ms
				freq_up=freq_up-freq_ch2;
				closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			}*/
		}
		
//		closest_frequency = gpioHardwarePWM(18, 0,500000);
		closest_frequency = gpioHardwarePWM(19, 0,500000);
		//closest_frequency = gpioHardwarePWM(13, 0,500000);
		sleep(1);
		
//		target_direction =1;
		target_direction_y1=1;
		target_direction_y2=0;
//		gpioWrite(25, target_direction);
		gpioWrite(7, target_direction_y1);	//Y1
		gpioWrite(24, target_direction_y2);	//Y2
		
		for(int i=0;i<freq_up_cnt;i++){
//			closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			Get = gpioGetPWMfrequency(18);
//			printf("freq: %d\n",Get);
			closest_frequency = gpioHardwarePWM(19, y+freq_up,500000);
			//closest_frequency = gpioHardwarePWM(13, 500+freq_up,500000);
			if(i<freq_up_cnt){
				usleep(10000);	 // 1000=1ms
				freq_up=freq_up+freq_ch;
			}
			/*else{
				usleep(5000);	//10ms
				freq_up=freq_up+freq_ch2;
				closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			}*/

		}
		usleep(std_time);
		
		for(int i=0;i<=freq_up_cnt;i++){
//			closest_frequency = gpioHardwarePWM(18, 500+freq_up,500000);
			Get = gpioGetPWMfrequency(18);
//			printf("freq: %d\n",Get);
			closest_frequency = gpioHardwarePWM(19, y+freq_up,500000);
			//closest_frequency = gpioHardwarePWM(13, 500+freq_up,500000);
			if(i<freq_up_cnt){
				usleep(10000);	//10ms
				freq_up=freq_up-freq_ch;
			}
			/*else{
				usleep(5000);	//10ms
				freq_up=freq_up-up-freq_ch;
				closest_frequency = gpioHardwarePWM(18, 500+freq_up2,500000);
			}*/
		}
//		closest_frequency = gpioHardwarePWM(18, 0,500000);
		Get = gpioGetPWMfrequency(18);
//		printf("freq: %d\n",Get);
		closest_frequency = gpioHardwarePWM(19, 0,500000);
		//closest_frequency = gpioHardwarePWM(13, 0,500000);
		sleep(1);
//		target_direction =0;
		target_direction_y1=0;
		target_direction_y2=1;
//		gpioWrite(25, target_direction);
		gpioWrite(7, target_direction_y1);	//Y1
		gpioWrite(24, target_direction_y2);	//Y2
		
		}
	
	
	return 0;
}

void sigcatch(int sig){
	int closest_frequency;
	
	printf("catch signal \n",sig);
	closest_frequency = gpioHardwarePWM(18, 0,500000);
	closest_frequency = gpioHardwarePWM(19, 0,500000);
	closest_frequency = gpioHardwarePWM(13, 0,500000);
	exit(1);
}

