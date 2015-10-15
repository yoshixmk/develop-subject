#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120

//---------------------------------------------------------------
//【関数名　】：cv_ColorExtraction
//【処理概要】：色抽出
//【引数　　】：src_img        = 入力画像(8bit3ch)
//　　　　　　：dst_img        = 出力画像(8bit3ch)
//　　　　　　：code        = 色空間の指定（CV_BGR2HSV,CV_BGR2Labなど）
//　　　　　　：ch1_lower    = ch1のしきい値(小)
//　　　　　　：ch1_upper    = ch1のしきい値(大)
//　　　　　　：ch2_lower    = ch2のしきい値(小)
//　　　　　　：ch2_upper    = ch2のしきい値(大)
//　　　　　　：ch3_lower    = ch3のしきい値(小)
//　　　　　　：ch3_upper    = ch3のしきい値(大)
//【戻り値　】：なし
//【備考　　】：lower <= upperの場合、lower以上upper以下の範囲を抽出、
//　　　　　　：lower >  upperの場合、upper以下lower以上の範囲を抽出します。
//---------------------------------------------------------------
void cv_ColorExtraction(IplImage* src_img, IplImage* dst_img,
                        int code,
                        int ch1_lower, int ch1_upper,
                        int ch2_lower, int ch2_upper,
                        int ch3_lower, int ch3_upper
                       ) {

    int i, k;

    IplImage *Color_img;
    IplImage *ch1_img, *ch2_img, *ch3_img;
    IplImage *Mask_img;

    int lower[3];
    int upper[3];
    int val[3];

    CvMat *lut;

    //codeに基づいたカラー変換
    Color_img = cvCreateImage(cvGetSize(src_img), src_img->depth, src_img->nChannels);
    cvCvtColor(src_img, Color_img, code);

    //3ChのLUT作成
    lut    = cvCreateMat(256, 1, CV_8UC3);

    lower[0] = ch1_lower;
    lower[1] = ch2_lower;
    lower[2] = ch3_lower;

    upper[0] = ch1_upper;
    upper[1] = ch2_upper;
    upper[2] = ch3_upper;

    for (i = 0; i < 256; i++) {
        for (k = 0; k < 3; k++) {
            if (lower[k] <= upper[k]) {
                if ((lower[k] <= i) && (i <= upper[k])) {
                    val[k] = 255;
                } else {
                    val[k] = 0;
                }
            } else {
                if ((i <= upper[k]) || (lower[k] <= i)) {
                    val[k] = 255;
                } else {
                    val[k] = 0;
                }
            }
        }
        //LUTの設定
        cvSet1D(lut, i, cvScalar(val[0], val[1], val[2]));
    }

    //3ChごとのLUT変換（各チャンネルごとに２値化処理）
    cvLUT(Color_img, Color_img, lut);
    cvReleaseMat(&lut);

    //各チャンネルごとのIplImageを確保する
    ch1_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    ch2_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    ch3_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);

    //チャンネルごとに二値化された画像をそれぞれのチャンネルに分解する
    cvSplit(Color_img, ch1_img, ch2_img, ch3_img, NULL);

    //3Ch全てのANDを取り、マスク画像を作成する。
    Mask_img = cvCreateImage(cvGetSize(Color_img), Color_img->depth, 1);
    cvAnd(ch1_img, ch2_img, Mask_img);
    cvAnd(Mask_img, ch3_img, Mask_img);

    //入力画像(src_img)のマスク領域を出力画像(dst_img)へコピーする
    cvZero(dst_img);
    cvCopy(src_img, dst_img, Mask_img);

    //解放
    cvReleaseImage(&Color_img);
    cvReleaseImage(&ch1_img);
    cvReleaseImage(&ch2_img);
    cvReleaseImage(&ch3_img);
    cvReleaseImage(&Mask_img);

}

const char* to_c_char(int val)
{
	std::stringstream stream;
	stream << val;
	return stream.str().c_str();
}

int main(int argc, char* argv[]) {
	int fps=30;
	time_t start,end;

	// OpenCV variables
	CvFont font;
	
    printf("start!\n");

	//pwm initialize
	if(gpioInitialise() < 0) return -1;
	//pigpio CW/CCW pin setup
	//X:18, Y1:14, Y2:15
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(14, PI_OUTPUT);
	gpioSetMode(15, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//limit-switch setup
	gpioSetMode(5, PI_INPUT);
	gpioWrite(5, 0);
	gpioSetMode(6, PI_INPUT);
	gpioWrite(6, 0);
	gpioSetMode(13, PI_INPUT);
	gpioSetMode(19, PI_INPUT);
	gpioSetMode(26, PI_INPUT);
	gpioSetMode(21, PI_INPUT);
 
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
	cvSetCaptureProperty(capture_robot_side,CV_CAP_PROP_FPS,fps);
	cvSetCaptureProperty(capture_human_side,CV_CAP_PROP_FPS,fps);

	// 画像の表示用ウィンドウ生成
	//cvNamedWindow("Previous Image", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("Now Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("pack", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mallett", CV_WINDOW_AUTOSIZE);
	
	printf("redy?\n");
	//決定ボタンが押されたらスタート
	//本番はコメントはずす
	/*while(gpioRead(25) == 0){	
		if(cv::waitKey(30) >= 0) {
            break;
        }
	}*/
	printf("go!\n");

	// 画像ファイルポインタの宣言
	IplImage* img_robot_side = cvQueryFrame(capture_robot_side);
	IplImage* img_human_side = cvQueryFrame(capture_human_side);
	IplImage* img_all_round = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	IplImage* img_all_round2  = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	IplImage* show_img  = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	IplImage* dst_img_mallett;
	IplImage* dst_img_pack;
	IplImage* dst_img2_mallett;
	IplImage* dst_img2_pack;
	cv::Mat dst_bright_cont;
	cv::Mat mat_frame1;
	cv::Mat mat_frame2;
	cv::Mat dst_img_v;
	
	//IplImage* -> Mat
	cv::Mat pre_src;
	cv::Mat pre_dst;
	int rotate_times = 0;
	//Create trackbar to change brightness
	int iSliderValue1 = 50;
	cvCreateTrackbar("Brightness", "pack", &iSliderValue1, 100);
	//Create trackbar to change contrast
	int iSliderValue2 = 50;
	cvCreateTrackbar("Contrast", "pack", &iSliderValue2, 100);
	int iBrightness  = iSliderValue1 - 50;
	double dContrast = iSliderValue2 / 50.0;
	img_robot_side = cvQueryFrame(capture_robot_side);
	img_human_side = cvQueryFrame(capture_human_side);
	while(1){

		img_robot_side = cvQueryFrame(capture_robot_side);
		img_human_side = cvQueryFrame(capture_human_side);

		// Init font
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);
		dst_img_mallett = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		dst_img_pack = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		dst_img2_mallett = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		dst_img2_pack = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);

		cvShowImage("pack", img_robot_side);
		cvShowImage("mallett", img_human_side);
		
		cvReleaseImage (&dst_img_mallett);
		cvReleaseImage (&dst_img_pack);
		cvReleaseImage (&dst_img2_mallett);
		cvReleaseImage (&dst_img2_pack);
		
        if(cv::waitKey(1) >= 0) {
            break;
        }
    }
    
    gpioTerminate();
    
    cvDestroyAllWindows();
	
	//Clean up used CvCapture*
	cvReleaseCapture(&capture_robot_side);
	cvReleaseCapture(&capture_human_side);
    //Clean up used images
    cvReleaseImage(&img_all_round);
    cvReleaseImage(&img_human_side);
    //cvReleaseImage(&img_all_round2);
    //cvReleaseImage(&show_img);
    cvReleaseImage(&img_robot_side);

    return 0;
}
