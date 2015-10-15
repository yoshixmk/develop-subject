//#include <opencv2/core/core.hpp>
//#include <opencv2/highgui/highgui.hpp>
//#include <opencv2/videoio.hpp>
//#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <math.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120

int main(int argc, char* argv[])
{
	CvCapture* capture_robot_side;
	CvCapture* capture_human_side;
    capture_robot_side = cvCaptureFromCAM(0);
	capture_human_side = cvCaptureFromCAM(1);
	// size設定
    cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	//fps設定
	cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FPS,30);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FPS,30);

	// 画像の表示用ウィンドウ生成
	cvNamedWindow("Now Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Now Image2", CV_WINDOW_AUTOSIZE);

	int cnt = 0;    // frame数
	int oldcnt = 0;    // 前フレーム数
	int64 nowTime = 0;   // 現時刻
	int64 diffTime = 0;   // 経過時間

	int fps = 0;    // 1秒のフレーム数
	const double f = (1000 / cv::getTickFrequency());

	cv::Point point(2, 28);

	int64 startTime = cv::getTickCount();
	// 画像ファイルポインタの宣言
	IplImage* img_robot_side;
	IplImage* img_human_side;
	while (1) {
		img_robot_side = cvQueryFrame(capture_robot_side);
		 img_human_side = cvQueryFrame(capture_human_side);
		
		nowTime = cv::getTickCount();
		diffTime = (int)((nowTime - startTime)*f);

		if (diffTime >= 1000) {
			startTime = nowTime;
			fps = cnt - oldcnt;
			oldcnt = cnt;
		}

		std::ostringstream os;
		os << fps;
		std::string number = os.str();

		//cv::putText(img_robot_side, number, point, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 200), 2, CV_AA);

		//cv::imshow("image", mat);
		cvShowImage("Now Image", img_robot_side);
		cvShowImage("Now Image2", img_human_side);
		
		int key = cv::waitKey(10);
		if (key == 'q') {
			break;
		}
		cnt++;
	}
	cvReleaseImage(&img_robot_side);
	cvReleaseImage(&img_human_side);

	//Clean up used CvCapture*
	cvReleaseCapture(&capture_robot_side);
	cvReleaseCapture(&capture_human_side);
	
	return 0;
}
