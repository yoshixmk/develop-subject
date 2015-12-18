#include "RobotMovement.h"

namespace UI {

/* シグナル受信/処理 */
void RobotMovement::signalHandler(int aSignal)
{
	std::cout << "SIGNAL Keybord Interrupt, END" <<std::endl;
	gpioTerminate();
    exit(0);
}

RobotMovement::RobotMovement()
{
	if (gpioInitialise() < 0)
	{
		std::cout << "pigpio initialisation failed." << std::endl;
	}
	else
	{
		std::cout << "pigpio initialised okay." << std::endl;
	}

	if (signal(SIGINT, &signalHandler) == SIG_ERR) {
		std::cout << "I could not set up signal. finished" <<std::endl;
		gpioTerminate();
		exit(1);
	}
}

RobotMovement::~RobotMovement()
{
	gpioTerminate();
}

void RobotMovement::move()
{
	std::cout<<"Robot Movement Run."<<std::endl;
	Hardware::Serial serial;
	Hardware::MotorDriver motorDriver(18, 25);
	char input[2];
	int isRead;
	double start_time;
	double now_time, passed_time;
	int frequencyX = 0;
	int frequencyY = 0;
	while(1){
		while(serial.serialDataAvailable()){
			start_time = time_time();
			isRead = serial.serialRead(input, 2);
			//暗黙のint変換。char->unsigned char->int
			//0~255 -> 0~2550Hz とするための、10倍
			if(isRead >= 0){
				frequencyX = (unsigned char)input[0] * 10 * 2;
				frequencyY = (unsigned char)input[1] * 10 * 2;
				std::cout << "X: " << frequencyX << std::endl;
				std::cout << "Y: " << frequencyY << std::endl;

				motorDriver.output(frequencyX, true);
				isRead = 0;
			}

			now_time = time_time();
			passed_time = now_time - start_time;
			std::cout << passed_time << std::endl;
		}
	}
}
} /* namespace UI */
