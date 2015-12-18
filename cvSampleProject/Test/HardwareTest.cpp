#include "HardwareTest.h"

namespace Test {
/* シグナル受信/処理 */
void HardwareTest::signalHandler(int aSignal) {
	std::cout << "SIGNAL Keybord Interrupt, END" << std::endl;
	exit(0);
}

HardwareTest::HardwareTest() {
	//gpioCfgClock(4, 0, 100);
	//if (gpioInitialise() < 0) {
	//	std::cout << "pigpio initialisation failed." << std::endl;
	//} else {
	//	std::cout << "pigpio initialised okay." << std::endl;
	//}

	//if (signal(SIGINT, &signalHandler) == SIG_ERR) {
	//	std::cout << "I could not set up signal. finished" << std::endl;
	//	gpioTerminate();
	//	exit(1);
	//}
}

HardwareTest::~HardwareTest() {
	//gpioTerminate();
}
//
//void HardwareTest::timerTest() {
//	std::cout << "!!!Timer Test!!!" << std::endl; // Timer Test start!
//
//	Hardware::Timer timer;
//
//	timer.setTimer(10.5);
//	while (!timer.getAlarm())
//		;
//	/*//while(!timer.getAlarm()){
//	 if(timer.getAlarm()){
//	 std::cout << "getAlarm() retun Bool OK." << std::endl;
//	 }
//	 else{
//	 std::cout << "getAlarm() retun Bool NG." << std::endl;
//	 }
//	 //}*/
//}
//
//void HardwareTest::raspberryPiSignalTest() {
//	Hardware::RaspberryPiSignal raspberryPiSignal(8);
//
//	std::cout << raspberryPiSignal.readLevel() << std::endl;
//}
//
//void HardwareTest::photoelectricSensorTest() {
//	Hardware::PhotoelectricSensor photoelectricSensor1(2);
//	Hardware::PhotoelectricSensor photoelectricSensor2(9);
//
//	std::cout << "phtoelectricSensor_test" << std::endl;
//	std::cout << photoelectricSensor1.readLevel() << std::endl;
//	std::cout << photoelectricSensor2.readLevel() << std::endl;
//}
//
//void HardwareTest::photomicrosensorTest() {
//	Hardware::Photomicrosensor photomicrosensorRight(16);
//	Hardware::Photomicrosensor photomicrosensorLeft(21);
//
//	std::cout << "photomicrosensor_test" << std::endl;
//	std::cout << photomicrosensorRight.readLevel() << std::endl;
//	std::cout << photomicrosensorLeft.readLevel() << std::endl;
//}
//
//void HardwareTest::limitSwitchTest() {
//	Hardware::LimitSwitch limitSwitch(5);
//
//	std::cout << "limitSwitch_test" << std::endl;
//	std::cout << limitSwitch.readLevel() << std::endl;
//}
//
//void HardwareTest::proximitySensorTest() {
//	Hardware::ProximitySensor proximitySensor(20);
//
//	std::cout << "proximitySensor_test" << std::endl;
//	std::cout << proximitySensor.readLevel() << std::endl;
//}
//
//void HardwareTest::pushSwitchTest() {
//	Hardware::PushSwitch pushSwitch1(10);
//	Hardware::PushSwitch pushSwitch2(11);
//
//	std::cout << "pushSwitch_test" << std::endl;
//	std::cout << pushSwitch1.readLevel() << std::endl;
//	std::cout << pushSwitch2.readLevel() << std::endl;
//}
//
//void HardwareTest::moterDriverTest() {
//	Hardware::MotorDriver moterDriverXAxis(25, 18);
//	Hardware::MotorDriver moterDriverY1Axis(23, 7);
//	Hardware::MotorDriver moterDriverY2Axis(24, 12);
//
//	std::cout << "moterDriver_test" << std::endl;
//	moterDriverXAxis.setPulse(1000);
//	//moterDriverXAxis.setCwCcw(1);
//	moterDriverXAxis.setCwCcw(0);
//	moterDriverXAxis.output();
//
//	Hardware::Timer timer;
//	timer.setTimer(5);
//	moterDriverXAxis.output();
//	while (!timer.getAlarm())
//		;
//
//	moterDriverXAxis.setPulse(2000);
//	timer.setTimer(5);
//	moterDriverXAxis.output();
//	while (!timer.getAlarm())
//		;
//
//	moterDriverXAxis.setPulse(2500);
//	timer.setTimer(5);
//	moterDriverXAxis.output();
//	while (!timer.getAlarm())
//		;
//}
//
//void HardwareTest::speakerTest() {
//	std::cout << "speaker_test" << std::endl;
//	Hardware::Speaker speaker_hisyo, speaker_sword_f, speaker_chui;
//	speaker_hisyo.setSoundTrack("hisyo.mp3", true);
//	speaker_hisyo.emitSound();
//	std::cout << "hisyo.mp3 emitted." << std::endl;
//	Hardware::Timer timer;
//	timer.setTimer(1);
//	while (!timer.getAlarm())
//		;
//
//	int i;
//	for (i = 0; i < 2; i++) {
//		speaker_sword_f.setSoundTrack("sword_f.mp3", false);
//		speaker_sword_f.emitSound();
//		std::cout << "sword_f.mp3 emitted." << std::endl;
//		timer.setTimer(1);
//		while (!timer.getAlarm())
//			;
//		if (i == 0) {
//			speaker_hisyo.stopSound();
//		}
//		timer.setTimer(1);
//		speaker_chui.setSoundTrack("chui.mp3", false);
//		speaker_chui.emitSound();
//		std::cout << "chui.mp3 emitted." << std::endl;
//		while (!timer.getAlarm())
//			;
//	}
//	speaker_chui.stopSound();
//	speaker_chui.stopSound();
//}
//
//void HardwareTest::bgmSignalTest() {
//	std::cout << "BGMSignal_test" << std::endl;
//	Hardware::BGMSignal bgmSignal(13);
//
//	bgmSignal.writeHigh();
////	bgmSignal.writeLow();
//}

void HardwareTest::cameraTest() {
	std::cout << "Camera_test" << std::endl;
	Hardware::Camera camera;
	Hardware::Camera camera2;

	cvNamedWindow("RobotSide", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("HumanSide", CV_WINDOW_AUTOSIZE);

	while (1) {
		Hardware::Camera camera3;
		Hardware::Camera::renew();
		cvShowImage("RobotSide", camera.getRobotSideImage());
		cvShowImage("HumanSide", camera2.getHumanSideImage());
		if (cv::waitKey(1) >= 0) {
			break;
		}
	}

}

}  // namespace Test
