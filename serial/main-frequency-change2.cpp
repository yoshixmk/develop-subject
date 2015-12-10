#include <opencv2/core/core.hpp>        // coreモジュールのヘッダーをインクルード
#include <opencv2/highgui/highgui.hpp>  // highguiモジュールのヘッダーをインクルード
#include <iostream>
#include <windows.h>
#include <tchar.h>

int main(int argc, const char* argv[])
{
	HANDLE comPort;

	comPort = CreateFile(_T("COM3"),                //port name
		GENERIC_READ | GENERIC_WRITE, //Read/Write
		0,                            // No Sharing
		NULL,                         // No Security
		OPEN_EXISTING,// Open existing port only
		0,            // Non Overlapped I/O
		NULL);        // Null for Comm Devices

	if (comPort == INVALID_HANDLE_VALUE)
		printf("Error in opening serial port");
	else
		printf("opening serial port successful");

	DCB dcb; // シリアルポートの構成情報が入る構造体
	GetCommState(comPort, &dcb); // 現在の設定値を読み込み

	dcb.BaudRate = 19200; // 速度
	dcb.ByteSize = 8; // データ長
	dcb.Parity = NOPARITY; // パリティ
	dcb.StopBits = ONESTOPBIT; // ストップビット長
	dcb.fOutxCtsFlow = FALSE; // ハードウェアフロー制御 送信時CTSフロー
	dcb.fOutX = FALSE; // ソフトウェアフロー制御 送信時XON/OFF制御の有無
	SetCommState(comPort, &dcb); // 変更した設定値を書き込み

	// 幅320px、高さ240pxで赤色の画像データを生成
	cv::Mat redImg(cv::Size(320, 240), CV_8UC3, cv::Scalar(0, 0, 255));

	// 画像表示用のウィンドウを生成
	cv::namedWindow("red", cv::WINDOW_AUTOSIZE);

	// キー入力を待機 frequency test
	DWORD numberOfPut;
	const char* sentData;
	DWORD lengthOfSent = 5; // 送信する文字数
	cv::imshow("red", redImg);
	sentData = "1000"; // 送信する文字列
	while (1){
		WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // ポートへ送信
		if (cv::waitKey(1) > 0){
			break;
		}
	}

	cv::imshow("red", redImg);
	sentData = "0"; // 送信する文字列
	while (1){
		WriteFile(comPort, sentData, lengthOfSent, &numberOfPut, NULL); // ポートへ送信
		if (cv::waitKey(1) > 0){
			break;
		}
	}

	CloseHandle(comPort);// Closing the Serial Port

	// 5作成したウィンドウを全て破棄
	cv::destroyAllWindows();

	return 0;
}
