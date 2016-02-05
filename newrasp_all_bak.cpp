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

/*　OS標準GPIOの割り当て	*/
/////////////////////////////////////////////////////////////////////////
#define rasp_sig 8	//スタート信号をラズベリーパイ間で共有する
#define limit 5	//リミットスイッチ
#define play_mode 1	//プレイモード切替
#define set_mode 0	//設定モード切替
#define level_s 10	//難易度：強　切替
#define level_w 11	//難易度：弱　切替
#define level_bgm 2	//難易度をラズベリーパイ間で共有する
#define stop_bgm 13	//外部BGMの停止
#define next_bgm 26	//外部BGMの再生（次曲へジャンプ）
#define motorX_direction		25	//Xモータ方向
#define motorY1_direction	7	//Y1モータ方向
#define motorY2_direction	24	//Y2モータ方向
#define motorX_pulse	18	//Xモータパルス
#define motorY_pulse	19	//Yモータパルス
#define fan	6	//ファンの出力
/////////既製品のドライバー//////////
#define x_direction_l   0			
#define y1_direction_f  1	
#define y2_direction_f  0
#define x_direction_r   1
#define y1_direction_b  0
#define y2_direction_b  1
/////////内藤ドライバー/////////////
/*#define x_direction_l   0			
#define y1_direction_f  0
#define y2_direction_f  1
#define x_direction_r   1
#define y1_direction_b  1
#define y2_direction_b  0*/
/////////////////////////////////////////////////////////////////////////

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
	
	//モータ方向用
	//X:25, Y1:7, Y2:24
	gpioSetMode(motorX_direction, PI_OUTPUT);
	gpioSetMode(motorY1_direction, PI_OUTPUT);
	gpioSetMode(motorY2_direction, PI_OUTPUT);
	//モータパルス用
	//X:18, Y:19
	gpioSetMode(motorX_pulse, PI_OUTPUT);
	gpioSetMode(motorY_pulse, PI_OUTPUT);
	
	//外部BGM停止
	gpioSetMode(stop_bgm, PI_OUTPUT);
	
	//外部BGM再生（次曲へジャンプ）
	gpioSetMode(next_bgm, PI_OUTPUT);
	
	//難易度BGM用
	gpioSetMode(level_bgm, PI_OUTPUT);
	
	//難易度用
	gpioSetMode(level_s, PI_INPUT);
	gpioSetMode(level_w, PI_INPUT);

	//raspberry間通信
	gpioSetMode(rasp_sig, PI_INPUT);
	
	//オーバラン＋原点復帰
	gpioSetMode(limit, PI_INPUT);
	
	//ファンの出力設定
	gpioSetMode(fan, PI_OUTPUT);
	
	gpioWrite(fan, 0);	//ファン:OFF
	
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
	int first_move = 0;
	int limit_flg = 0;		//周波数が400以上だったらリミットの処理を抜ける
	int limit_flg2 = 0;	//リミットがLOWになるまでリミットの処理をしない
	
	gpioWrite(level_bgm, 1); //デフォルトの難易度は強
	
	if(SIG_ERR == signal(SIGINT,sigcatch)){	//プログラム終了時にモータを止める
		printf("fail");
		exit(1);
	}
	
	sleep(5);
	
	gpioWrite(next_bgm, 0);	//外部BGM:Next
	
	gpioWrite(stop_bgm, 0);	//外部BGM:ON:OFF

	gpioWrite(fan, 1);	//ファン:ON

	while(1){
		usleep(1);
	//	printf("%d\n",gpioRead(rasp_sig));
		if(gpioRead(rasp_sig)== play_mode){
			if(bgm==1){
				gpioWrite(next_bgm, 1);	//外部BGM
				usleep(100000);
				gpioWrite(next_bgm, 0);	//外部BGM
				printf("play_mode\n");
				gpioWrite(fan, 1);	//ファン:ON
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
					std::cout << "X1: " << frequencyX << std::endl;
					std::cout << "Y1: " << frequencyY << std::endl;
//					std::cout << "mallet_X1: " << mallet_X << std::endl;
//					std::cout << "mallet_Y1: " << mallet_Y << std::endl;
//					std::cout << "DIST: " << direction << std::endl;
					//std::cout << std::flush;
				
					if(direction != predirection){
							if(direction  == 'A'){	
								gpioWrite(motorX_direction, x_direction_l);	//X左
								gpioWrite(motorY1_direction, y1_direction_f);//Y前
								gpioWrite(motorY2_direction, y2_direction_f);
							}
							else if(direction  == 'B'){	
								gpioWrite(motorX_direction, x_direction_r);	//X右
								gpioWrite(motorY1_direction, y1_direction_f);//Y前
								gpioWrite(motorY2_direction, y2_direction_f);
							}
							else if(direction  == 'C'){	
								gpioWrite(motorX_direction, x_direction_r);	//X右
								gpioWrite(motorY1_direction, y1_direction_b);//Y後
								gpioWrite(motorY2_direction, y2_direction_b);
							}
							else if(direction  == 'D'){	
								gpioWrite(motorX_direction, x_direction_l);	//X左
								gpioWrite(motorY1_direction, y1_direction_b);//Y後
								gpioWrite(motorY2_direction, y2_direction_b);
							}	
						predirection = direction;
					}	

					usleep(500);	//500
					
					if(gpioRead(limit) == HIGH && limit_flg2 == 0){//オーバラン(リミットが反応）したときに止める
						printf("limit\n");
						f = gpioHardwarePWM(motorX_pulse, 0, 500000);
						f = gpioHardwarePWM(motorY_pulse, 0, 500000);
						limit_flg = 1;
						
						if(frequencyX >= 400){		//周波数400がきたらオーバーランから抜ける
							printf("limit_freq_x:%dHz\n",frequencyX);
							limit_flg = 0;
							preFrequencyX = 0;
							preFrequencyY = 0;
							limit_flg2 = 1;
						}	
					}
					else if(gpioRead(limit) == LOW){
						limit_flg2 = 0;
						limit_flg = 0;
						preFrequencyX = 0;
						preFrequencyY = 0;
						
					}
				
					if(frequencyY != preFrequencyY && limit_flg==0){
						//printf("motor_move\n");
						if(frequencyX != preFrequencyX){
							f = gpioHardwarePWM(motorX_pulse, frequencyX, 500000);
							printf("freq_x:%dHz\n",frequencyX);
							preFrequencyX = frequencyX;
						}
						f = gpioHardwarePWM(motorY_pulse, frequencyY, 500000);
						preFrequencyY = frequencyY;
					}
						
					else if(frequencyX != preFrequencyX && limit_flg==0){
						f = gpioHardwarePWM(motorX_pulse, frequencyX, 500000);
						preFrequencyX = frequencyX;
					}
					
					isRead = 0;

				}

				now_time = time_time();
				usleep(1);
				if(gpioRead(rasp_sig)== set_mode){
					break;
				}	
			}
			gpioUSleep();	
		}
		
		if(gpioRead(rasp_sig) == set_mode){
			
			printf("set_mode\n");
			if(power_on == 1){		//電源起動時にはBGMを鳴らさない
				gpioWrite(stop_bgm, 1);	//外部BGM
				usleep(100000);
				gpioWrite(stop_bgm, 0);	//外部BGM
				printf("limit_modosi\n");					//電源起動時のリミット戻し
				if(mallet_X <= 160 && mallet_Y < 380){		//A（左前）方向にマレットが移動しているとき
					//リミットが反応しなくなる位置まで戻る
					//printf("A\n");
					gpioWrite(motorX_direction, x_direction_r);	//X右
					gpioWrite(motorY1_direction, y1_direction_b);	//Y後
					gpioWrite(motorY2_direction, y2_direction_b);
					f = gpioHardwarePWM(motorX_pulse, 200, 500000);
					f = gpioHardwarePWM(motorY_pulse, 200, 500000);
					usleep(100000);
				}
				else if(mallet_X > 160 && mallet_Y < 380){	//B（右前）方向にマレットが移動しているとき
					//printf("B\n");
					gpioWrite(motorX_direction, x_direction_l);	//X左
					gpioWrite(motorY1_direction, y1_direction_b);	//Y後
					gpioWrite(motorY2_direction, y2_direction_b);
					f = gpioHardwarePWM(motorX_pulse, 200, 500000);
					f = gpioHardwarePWM(motorY_pulse, 200, 500000);
					usleep(100000);
				}
				else if(mallet_X > 160 && mallet_Y > 380){	//C（右後）方向にマレットが移動しているとき
					//printf("C\n");
					gpioWrite(motorX_direction, x_direction_l);	//X左
					gpioWrite(motorY1_direction, y1_direction_f);	//Y前
					gpioWrite(motorY2_direction, y2_direction_f);
					f = gpioHardwarePWM(motorX_pulse, 200, 500000);
					f = gpioHardwarePWM(motorY_pulse, 200, 500000);
					usleep(100000);
				}
				else if(mallet_X <= 160 && mallet_Y > 380){	//D（左後）方向にマレットが移動しているとき
					//printf("D\n");
					gpioWrite(motorX_direction, x_direction_r);	//X右
					gpioWrite(motorY1_direction, y1_direction_f);	//Y前
					gpioWrite(motorY2_direction, y2_direction_f);
					f = gpioHardwarePWM(motorX_pulse, 200, 500000);
					f = gpioHardwarePWM(motorY_pulse, 200, 500000);
					usleep(100000);
				}
				f = gpioHardwarePWM(motorX_pulse, 0, 500000);
				f = gpioHardwarePWM(motorY_pulse, 0, 500000);
			}
			else{
				power_on = 1;
			}
			gpioWrite(fan, 0);	//ファン:OFF
		
			//Y軸を左上原点に戻す
			gpioWrite(motorY1_direction, y1_direction_f);	//後
			gpioWrite(motorY2_direction, y2_direction_f);
			usleep(1);
			while(gpioRead(limit) == LOW){
					f = gpioHardwarePWM(motorY_pulse, 300, 500000);
					printf("move_on\n");
					usleep(1);
					while(gpioRead(limit) == LOW){
						usleep(500);
					}
			}
			f = gpioHardwarePWM(motorY_pulse, 0, 500000);
			gpioWrite(motorY1_direction, y1_direction_b);	//前
			gpioWrite(motorY2_direction, y2_direction_b);
			f = gpioHardwarePWM(motorY_pulse, 200, 500000);
			usleep(500000);
			f = gpioHardwarePWM(motorY_pulse, 0, 500000);
			
			
			//X軸を原点に戻す
			gpioWrite(motorX_direction,x_direction_l);	//Xを左に動かす
			usleep(1);
			while(gpioRead(limit) == LOW){	//x左のリミットに当たるまで移動
					f = gpioHardwarePWM(motorX_pulse, 400, 500000);
					printf("move_left\n");
					usleep(1);
					while(gpioRead(limit) == LOW){
						usleep(500);
						//printf("sleep\n");
					}
			}
			
			f = gpioHardwarePWM(motorX_pulse, 0, 500000);
			gpioWrite(motorX_direction, x_direction_r);	//Xを中央に動かす
			f = gpioHardwarePWM(motorX_pulse, 235, 500000);
			sleep(3);
			f = gpioHardwarePWM(motorX_pulse, 0, 500000);
			
			//Y軸を下に下ろす
			gpioWrite(motorY1_direction, y1_direction_b);	//後
			gpioWrite(motorY2_direction, y2_direction_b);
			f = gpioHardwarePWM(motorY_pulse, 345, 500000);
			sleep(2);
			/*
			while(gpioRead(limit) == LOW){
					f = gpioHardwarePWM(motorY_pulse, 300, 500000);
					printf("move_under\n");
					usleep(1);
					while(gpioRead(limit) == LOW){
						usleep(500);
					}
			}
			f = gpioHardwarePWM(motorY_pulse, 0, 500000);
			gpioWrite(motorY1_direction, y1_direction_f);	//前
			gpioWrite(motorY2_direction, y2_direction_f);
			f = gpioHardwarePWM(motorY_pulse, 200, 500000);
			usleep(500000);
			*/
			f = gpioHardwarePWM(motorY_pulse, 0, 500000);
						
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


