#include <stdio.h>
#include <string.h>

#include <wiringPi.h>
#include <wiringSerial.h>

int main(){

/* シリアルポートオープン */
int fd = serialOpen("/dev/ttyAMA0",115200);
if(fd<0){
printf("can not open serialport");
}

while(1){
/* 受信処理 */
while(serialDataAvail(fd)){
printf("recive : %c" , serialGetchar(fd) );
fflush(stdout);
}

/* 送信処理 */
serialPuts(fd,"hello world\n");

delay(1000);
}

return;
}