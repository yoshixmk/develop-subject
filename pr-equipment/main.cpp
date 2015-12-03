#include "Test/HardwareTest.h"
#include "Test/ColorTest.h"
#include "Test/StrategyTest.h"
#include "Test/UITest.h"
#include "Test/ShowWindowTest.h"

int main() {
	Test::HardwareTest hardwareTest;
//	hardwareTest.timerTest();
	//hardwareTest.raspberryPiSignalTest();
	//hardwareTest.photoelectricSensor();
	//hardwareTest.photomicrosensor();
	//hardwareTest.limitSwitch();
	//hardwareTest.proximitySensor();
	//hardwareTest.pushSwitchTest();
//	hardwareTest.moterDriverTest();
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
//	strategyTest.frequencySwitchingTest();
//	strategyTest.frequencySwitching_X_Test();
//	strategyTest.frequencySwitching_Y_Test();
//	strategyTest.frequencyTest();
//	strategyTest.frequency_X_Test();
//	strategyTest.frequency_Y_Test();
	strategyTest.robotActionTest();

	Test::UITest uiTest;
//	uiTest.intelligentTest();
//	uiTest.soundTest();

	Test::ShowWindowTest showWindowTest;
//	showWindowTest.windowTest();
//	showWindowTest.drawingTest();
	return 0;
}
