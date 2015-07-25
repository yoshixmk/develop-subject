#include <opencv2/core/core.hpp>
#include <opencv2/highgui/highgui.hpp>
#include <opencv2/imgproc/imgproc.hpp>
#include <iostream>
#include <opencv2/opencv.hpp>
#include <time.h>
#include <math.h>

int main(int argc, char** argv[])
{
	cv::VideoCapture mCap;     // camera device
	cv::Mat mat;

	int cnt = 0;    // frame数
	int oldcnt = 0;    // 前フレーム数
	int64 nowTime = 0;   // 現時刻
	int64 diffTime = 0;   // 経過時間

	int fps = 0;    // 1秒のフレーム数
	const double f = (1000 / cv::getTickFrequency());

	mCap.open(0);
	mCap.set(CV_CAP_PROP_FPS, 20);
	mCap.set(CV_CAP_PROP_FRAME_WIDTH, 640);
	mCap.set(CV_CAP_PROP_FRAME_HEIGHT, 480);

	cv::Point point(2, 28);

	int64 startTime = cv::getTickCount();
	while (1) {
		mCap >> mat;

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

		cv::putText(mat, number, point, cv::FONT_HERSHEY_SIMPLEX, 1, cv::Scalar(0, 0, 200), 2, CV_AA);

		cv::imshow("image", mat);

		int key = cv::waitKey(10);

		if (key == 'q') {
			break;
		}
		cnt++;
	}

	return 0;
}
