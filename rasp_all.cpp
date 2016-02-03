#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <iostream>
#include <signal.h>
#include <termios.h>
#include <wiringPi.h>
#include <float.h>

#define rasp_sig 8

#define limit 5

#define play_mode 1
#define set_mode 0
#define level_s 10
#define level_w 11
#define level_bgm 2

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
	exit(1);
}

int main(int argc, char* argv[]) 
{

	
	if(gpioInitialise() < 0) return -1;
	
	//pigpio CW/CCW pin setup
	//X:18, Y1:14, Y2:15
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(7, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(19, PI_OUTPUT);
	
	//外部BGM用
	gpioSetMode(13, PI_OUTPUT);
	
	//難易度BGM用
	gpioSetMode(level_bgm, PI_OUTPUT);
	
	//難易度用
	gpioSetMode(level_s, PI_INPUT);
	gpioSetMode(level_w, PI_INPUT);

	//raspberry間通信
	gpioSetMode(rasp_sig, PI_INPUT);
	
	//オーバラン＋原点復帰
	gpioSetMode(limit, PI_INPUT);
	
	gpioWrite(6, 0);	//ファン:OFF
	
	char sertty[] = "/dev/ttyAMA0";
	handle = serOpen(sertty, 115200, 0);
	
	if(handle>=0){
		std::cout << "OK, serial port open" << std::endl;
	}
	else{
		std::cout << "NG, serial port cannnot open" << std::endl;
	}
	const char *cmd1 = "sudo mpg321 -q 'hayai.mp3' &";
	char input[] = {0};
	double start_time;
	double now_time, passed_time;
	char direction = '\0';
	char predirection = '\0';
	int frequencyX = 0;
	int frequencyY = 0;
	int mallet_X = 0;
	int mallet_Y = 0;
	int preFrequencyX = 0;
	int preFrequencyY = 0;
	//char distination;
	int isRead = 0;
	int i;
	int f;
	int bgm = 0;	//外部BGMの処理を一度だけ行うための変数
	int level = 0;	//難易度(0:強 1:弱)
	int power_on = 0;	//電源起動時にはBGMを鳴らさない
	
	
	gpioWrite(level_bgm, 1); //デフォルトの難易度は強
	
	if(SIG_ERR == signal(SIGINT,sigcatch)){	//プログラム終了時にモータを止める
		printf("fail");
		exit(1);
	}
	
	sleep(5);
	
	gpioWrite(26, 0);	//外部BGM:Next
	
	gpioWrite(13, 0);	//外部BGM:ON:OFF
	
	/*
	while(1){
		
		printf("playpause\n");
		gpioWrite(13, 1);	//外部BGM
		usleep(100000);
		gpioWrite(13, 0);	//外部BGM
		sleep(5);
		printf("next\n");
		gpioWrite(26, 1);	//外部BGM
		usleep(100000);
		gpioWrite(26, 0);	//外部BGM
		sleep(5);
	}*/

	while(1){
		usleep(1);
	//	printf("%d\n",gpioRead(rasp_sig));
		if(gpioRead(rasp_sig)== play_mode){
			if(bgm==1){
				gpioWrite(26, 1);	//外部BGM
				usleep(100000);
				gpioWrite(26, 0);	//外部BGM
				printf("play_mode\n");
				gpioWrite(6, 1);	//ファン:ON
			}
			bgm=0;
			start_time = time_time();

			while(serDataAvailable(handle)){
				start_time = time_time();
				isRead = serRead(handle, input, 8);
				//暗黙のint変換。char->unsigned char->int
				//0~255 -> 0~2550Hz とするための、10倍
				if(isRead >= 0){
					if(level == 0){	//難易度が強のとき
						frequencyX = (unsigned char)input[0] * 10 * 2;
						frequencyY = (unsigned char)input[1] * 10 * 2;
						direction  = (unsigned char)input[2];
					}
					else{				//難易度が弱のとき
						frequencyX = (unsigned char)input[3] * 10 * 2;
						frequencyY = (unsigned char)input[4] * 10 * 2;
						direction  = (unsigned char)input[5];
					}
						mallet_X = (unsigned char)input[6] * 2;
						mallet_Y = (unsigned char)input[7] * 2;
						std::cout << "X: " << frequencyX << std::endl;
						std::cout << "Y: " << frequencyY << std::endl;
						std::cout << "mallet_X: " << mallet_X << std::endl;
						std::cout << "mallet_Y: " << mallet_Y << std::endl;
						std::cout << "DIST: " << direction << std::endl;
						//std::cout << std::flush;
					
					if(direction != predirection){
							if(direction  == 'A'){	
								gpioWrite(25, 0);	//X左
								gpioWrite(7, 1);	//Y前
								gpioWrite(24, 0);
								//printf("AAA\n");
							}
							else if(direction  == 'B'){	
								gpioWrite(25, 1);	//X右
								gpioWrite(7, 1);	//Y前
								gpioWrite(24, 0);
								//printf("BBB\n");
							}
							else if(direction  == 'C'){	
								gpioWrite(25, 1);	//X右
								gpioWrite(7, 0);	//Y後
								gpioWrite(24, 1);
								//printf("CCC\n");
							}
							else if(direction  == 'D'){	
								gpioWrite(25, 0);	//X左
								gpioWrite(7, 0);	//Y後
								gpioWrite(24, 1);
								//printf("DDD\n");
							}	
						predirection = direction;
					}	

					if(gpioRead(limit) == HIGH){		//オーバランしたときに止める
						if(direction == 'A'){		//A方向にマレットが移動しているとき
							f = gpioHardwarePWM(19, 0, 500000);
							f = gpioHardwarePWM(18, 0, 500000);
						}
						else if(direction == 'B'){	//B方向にマレットが移動しているとき
						
						}
						else if(direction == 'C'){
							
						}
						else if(direction == 'D'){
							
						}
					}
					
					else if(frequencyY != preFrequencyY){	
						f = gpioHardwarePWM(19, frequencyY, 500000);
						preFrequencyY = frequencyY;
					}
						
					else if(frequencyX != preFrequencyX){
						f = gpioHardwarePWM(18, frequencyX, 500000);
						preFrequencyX = frequencyX;
					}
					
					isRead = 0;
				}
				now_time = time_time();
				//std::cout << now_time - start_time << std::endl;
				usleep(1);
				if(gpioRead(rasp_sig)== set_mode){
					break;
				}	
			}
			gpioUSleep();
			//std::cout << std::flush;
			//if(frequencyX == 5100){
			//	break;
			//}
	
			
		}
		
		else if(gpioRead(rasp_sig)== set_mode){
			
			printf("set_mode\n");
			if(power_on == 1){		//電源起動時にはBGMを鳴らさない
				gpioWrite(13, 1);	//外部BGM
				usleep(100000);
				gpioWrite(13, 0);	//外部BGM
			}
			else{
				power_on = 1;
			}
			gpioWrite(6, 0);	//ファン:OFF

			//X軸を原点に戻す
			gpioWrite(25, 0);	//Xを左に動かす
			usleep(1);
			while(gpioRead(limit) == LOW){	//x左のリミットに当たるまで移動
					f = gpioHardwarePWM(18, 400, 500000);
					printf("move_left\n");
					usleep(1);
					while(gpioRead(limit) == LOW){
						usleep(500);
						//printf("sleep\n");
					}
			}
			
			f = gpioHardwarePWM(18, 0, 500000);
			gpioWrite(25, 1);	//Xを左に動かす
			f = gpioHardwarePWM(18, 100, 500000);
			usleep(500000);
			f = gpioHardwarePWM(18, 0, 500000);
			
			//Y軸を原点に戻す
			gpioWrite(7, 0);	//後
			gpioWrite(24, 1);
			usleep(1);
			while(gpioRead(limit) == LOW){
					f = gpioHardwarePWM(19, 400, 500000);
					printf("move_under\n");
					usleep(1);
					while(gpioRead(limit) == LOW){
						usleep(10);
					}
			}
			f = gpioHardwarePWM(19, 0, 500000);
			gpioWrite(7, 1);	//前
			gpioWrite(24, 0);
			f = gpioHardwarePWM(19, 200, 500000);
			usleep(500000);
			f = gpioHardwarePWM(19, 0, 500000);
			/*			
			while(1){
				if(gpioRead(limit) == HIGH){
						printf("HIGH\n");
						sleep(1);
				}
			}
			*/		
			while(gpioRead(rasp_sig) == set_mode){
				if(gpioRead(level_s) == HIGH){
					printf("難易度:強\n");
					level = 0;
					gpioWrite(level_bgm, 1);
					while(gpioRead(level_s) == HIGH);
				}
				else if(gpioRead(level_w) == HIGH){
					printf("難易度:弱\n");
					level = 1;
					gpioWrite(level_bgm, 0);
					while(gpioRead(level_w) == HIGH);
				}
				
				usleep(10);
			}
			bgm=1;
			printf("exit\n");
		}
	}
	
	return 0;
}


