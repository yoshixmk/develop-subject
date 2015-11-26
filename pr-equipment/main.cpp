#include "Test/HardwareTest.h"
#include "Test/ColorTest.h"
#include "Test/StrategyTest.h"
#include "Test/UITest.h"
#include "Test/ShowWindowTest.h"

int main() {
	Test::HardwareTest hardwareTest;
	//hardware_test.timerTest();
	//hardware_test.raspberryPiSignalTest();
	//hardware_test.photoelectricSensor();
	//hardware_test.photomicrosensor();
	//hardware_test.limitSwitch();
	//hardware_test.proximitySensor();
	//hardwareTest.pushSwitchTest();
	//hardwareTest.moterDriverTest();
	//hardwareTest.speakerTest();
//	hardwareTest.bgmSignalTest();
//	hardwareTest.cameraTest();

	Test::ColorTest colorTest;
//	colorTest.twoImageSynthesisTest();
//	colorTest.hockeyTableMaskingTest();
//	colorTest.robotSideHockeyTableMaskingTest();
//	colorTest.perspectiveTransformationTest();
//	colorTest.colorExtractionTest();

	Test::StrategyTest strategyTest;
	//strategyTest.anomalyDetectionTest();
//	strategyTest.packCoordinateTest();
//	strategyTest.malletCoordinateTest();
//	strategyTest.frameCoordinateTest();
//	strategyTest.locusTest();

	Test::UITest uiTest;
//	uiTest.intelligentTest();
//	uiTest.soundTest();

	Test::ShowWindowTest showWindowTest;
//	showWindowTest.windowTest();
	showWindowTest.drawingTest();
	return 0;
}
