#include <stdio.h>
#include <stdlib.h>
#include <string>

int main(void){

}

void effect_play(void){
	system("mpg321 -q chui/chui.mp3 &");
}

void bgm_play(void){
	system("mpg321 -l 0 -q chui/chui.mp3 &");
}

void sound_stop(void){
	system("killall mpg321");
}
