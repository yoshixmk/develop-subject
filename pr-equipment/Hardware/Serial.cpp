#include "Serial.h"

namespace Hardware {

Serial::Serial() {
	serialOpen();
}

Serial::~Serial() {
	serialClose();
}

void Serial::serialOpen()
{
	char sertty[] = "/dev/ttyAMA0";
	mHandle = serOpen(sertty, 115200, 0);

	if(mHandle>=0){
		std::cout << "OK, serial port open" << std::endl;
	}
	else{
		std::cout << "NG, serial port cannnot open" << std::endl;
		std::exit(-1);
	}
}

void Serial::serialClose()
{
	serClose(mHandle);
}

int Serial::serialRead(char* aBuf, int aBytes)
{
	while(serDataAvailable(mHandle)){
		mIsRead = serRead(mHandle, aBuf, aBytes);
		//暗黙のint変換。char->unsigned char->int
		//0~255 -> 0~2550Hz とするための、10倍
		if(mIsRead >= 0){
//			frequencyX = (unsigned char)mInput[0] * 10 * 2;
//			frequencyY = (unsigned char)mInput[1] * 10 * 2;
//			std::cout << "X: " << frequencyX << std::endl;
//			std::cout << "Y: " << frequencyY << std::endl;
			mIsRead = 0;
		}
	}
	return mIsRead;
}

int Serial::serialDataAvailable()
{
	return serDataAvailable(mHandle);
}

} /* namespace Hardware */
