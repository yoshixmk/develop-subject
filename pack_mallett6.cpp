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

// All units in milimeters
#define robot_center_x 300   // Center of robot
#define robot_center_y 500

#define CAM_PIX_WIDTH 640
#define CAM_PIX_HEIGHT 480
#define CAM_PIX_TO_MM 1.4

time_t start,end;

// Parameters (with default values)
char comPort[20] = "COM19";
//white Pack
int minH=0;
int maxH=1;
int minS=0;
int maxS=3;
int minV=80;
int maxV=100;
//green  ROBOT MARK
int RminH=80;
int RmaxH=150;
int RminS=60;
int RmaxS=105;
int RminV=40;
int RmaxV=105;
int fps=30;
int viewWindow=1;

// OpenCV variables
CvFont font;
CvVideoWriter* record;
IplImage* imgTracking;
IplImage* imgThresh;
IplImage* imgThresh2;
IplImage* frame=0;
int lastX = -1;
int lastY = -1;
int posX;
int posY;
int objectSize;
int RposX;
int RposY;
int RobjectSize;
int status;

FILE* logFile;
char tempStr[80];
char logStr[4096];

// Trajectory prediction
// Puck variables
int puckCoordX;
int puckCoordY;
int puckOldCoordX;
int puckOldCoordY;
int puckSpeedX;
int puckSpeedY;
float puckSpeed;         // mm/sec
float puckDirection;     // radians

int defense_position;
int predict_x;    // X position at impact (mm)
int predict_y;
int predict_x_old;
int predict_y_old;
int predict_time;   // time to impact in ms
char tempStr2[80];

// Camera variables
int cam_center_x;
int cam_center_y;
float cam_pix_to_mm;
float cam_rotation;  //Camera rotation in radians

void cameraProcessInit()
{
    // Default values
    cam_center_x = CAM_PIX_WIDTH/2;
    cam_center_y = CAM_PIX_HEIGHT/2;
    cam_pix_to_mm = CAM_PIX_TO_MM;
    cam_rotation = 0; //radians  1º = 0.01745 2º = 0.035 4º = 0.07 5º = 0.087
    predict_x_old = -1;
    defense_position = 100;  // Pusher defense position
}

//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV, int minH, int maxH, int minS, int maxS, int minV, int maxV) {
    IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
    cvInRangeS(imgHSV, cvScalar(minH,minS,minV), cvScalar(maxH,maxS,maxV), imgThresh);
    return imgThresh;
}

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

//タイマー制御用関数。時間が経ったらリセット
void pwmReset(void){
	gpioWrite(18, 0);
	//gpioSetPWMfrequency(18, 0);
	gpioSetTimerFunc(0, 6000, NULL);
}

int main(int argc, char* argv[]) {
    printf("start!\n");

    printf("PUCK MINH: %d\n",minH);
    printf("PUCK MAXH: %d\n",maxH);
    printf("PUCK MINS: %d\n",minS);
    printf("PUCK MAXS: %d\n",maxS);
    printf("PUCK MINV: %d\n",minV);
    printf("PUCK MAXV: %d\n",maxV);
    printf("ROBOT MINH: %d\n",RminH);
    printf("ROBOT MAXH: %d\n",RmaxH);
    printf("ROBOT MINS: %d\n",RminS);
    printf("ROBOT MAXS: %d\n",RmaxS);
    printf("ROBOT MINV: %d\n",RminV);
    printf("ROBOT MAXV: %d\n",RmaxV);
    printf("FPS: %d\n",fps);

	//pwm initialize
	if(gpioInitialise() < 0) return -1;
	gpioSetMode(18, PI_OUTPUT);
	gpioSetMode(19, PI_OUTPUT);
 
	CvCapture* capture =0;
    capture = cvCaptureFromCAM(CV_CAP_ANY);
	// size設定
    cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_WIDTH,CAM_PIX_WIDTH);
	cvSetCaptureProperty(capture,CV_CAP_PROP_FRAME_HEIGHT,CAM_PIX_HEIGHT);
	//fps設定
	cvSetCaptureProperty(capture,CV_CAP_PROP_FPS,fps);

	// 画像の表示用ウィンドウ生成
	cvNamedWindow("Previous Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Now Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("pack", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mallett", CV_WINDOW_AUTOSIZE);
	
	//Create trackbar to change brightness
	int iSliderValue1 = 50;
	cvCreateTrackbar("Brightness", "Now Image", &iSliderValue1, 100);
	//Create trackbar to change contrast
	int iSliderValue2 = 50;
	cvCreateTrackbar("Contrast", "Now Image", &iSliderValue2, 100);
	//pack threthold 0, 50, 120, 220, 100, 220
	int iSliderValuePack1 = 80;
	cvCreateTrackbar("minH", "pack", &iSliderValuePack1, 255);
	int iSliderValuePack2 = 106;
	cvCreateTrackbar("maxH", "pack", &iSliderValuePack2, 255);
	int iSliderValuePack3 = 219;
	cvCreateTrackbar("minS", "pack", &iSliderValuePack2, 255);
	int iSliderValuePack4 = 255;
	cvCreateTrackbar("maxS", "pack", &iSliderValuePack4, 255);
	int iSliderValuePack5 = 29;
	cvCreateTrackbar("minV", "pack", &iSliderValuePack5, 255);
	int iSliderValuePack6 = 203;
	cvCreateTrackbar("maxV", "pack", &iSliderValuePack6, 255);
	//mallett threthold 0, 255, 100, 255, 140, 200
	int iSliderValueMallett1 = 106;
	cvCreateTrackbar("minH", "mallett", &iSliderValueMallett1, 255);
	int iSliderValueMallett2 = 135;
	cvCreateTrackbar("maxH", "mallett", &iSliderValueMallett2, 255);
	int iSliderValueMallett3 = 140;
	cvCreateTrackbar("minS", "mallett", &iSliderValueMallett3, 255);
	int iSliderValueMallett4 = 255;
	cvCreateTrackbar("maxS", "mallett", &iSliderValueMallett4, 255);
	int iSliderValueMallett5 = 0;
	cvCreateTrackbar("minV", "mallett", &iSliderValueMallett5, 255);
	int iSliderValueMallett6 = 255;
	cvCreateTrackbar("maxV", "mallett", &iSliderValueMallett6, 255);
	
	// 画像ファイルポインタの宣言
	IplImage* img = cvQueryFrame(capture);
	IplImage* img2  = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	IplImage* show_img  = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
	//IplImage* -> Mat
	cv::Mat pre_src;
	cv::Mat pre_dst;
	pre_src = cv::cvarrToMat(img);
	int iBrightness  = iSliderValue1 - 50;
	double dContrast = iSliderValue2 / 50.0;
	pre_src.convertTo(pre_dst, -1, dContrast, iBrightness); 
	//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
	*img = pre_dst;
	pre_src.release();
	
	printf("redy?\n");
	//決定ボタンが押されたらスタート
	//本番はコメントはずす
	/*while(gpioRead(25) == 0){	
		if(cv::waitKey(30) >= 0) {
            break;
        }
	}*/
	printf("go!\n");
	
	cv::Mat dst;
	int rotate_times = 0;
	while(1){		
		img2 = cvCloneImage(img);
		show_img = cvCloneImage(img);
		img = cvQueryFrame(capture);
		//IplImage* -> Mat
		cv::Mat src = cv::cvarrToMat(img);
		int iBrightness  = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		src.convertTo(dst, -1, dContrast, iBrightness); 
		//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
		*img = dst;
		src.release();
		
		// Init font
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);
		IplImage* dst_img_mallett = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
		IplImage* dst_img_pack = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
		IplImage* dst_img2_mallett = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, 3);
		IplImage* dst_img2_pack = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, 3);

		cv_ColorExtraction(img, dst_img_pack, CV_BGR2HSV, iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);
		cv_ColorExtraction(img, dst_img_mallett, CV_BGR2HSV, iSliderValueMallett1, iSliderValueMallett2, iSliderValueMallett3, iSliderValueMallett4, iSliderValueMallett5, iSliderValueMallett6);
		cv_ColorExtraction(img2, dst_img2_pack, CV_BGR2HSV, iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);
		
		//CvMoments moment_mallett;
		CvMoments moment_pack;
		CvMoments moment_mallett;
		CvMoments moment2_pack;
		//cvSetImageCOI(dst_img_mallett, 1);
		cvSetImageCOI(dst_img_pack, 1);
		cvSetImageCOI(dst_img_mallett, 1);
		cvSetImageCOI(dst_img2_pack, 1);

		//cvMoments(dst_img_mallett, &moment_mallett, 0);
		cvMoments(dst_img_pack, &moment_pack, 0);
		cvMoments(dst_img_mallett, &moment_mallett, 0);
		cvMoments(dst_img2_pack, &moment2_pack, 0);

		//座標計算
		double m00_before = cvGetSpatialMoment(&moment2_pack, 0, 0);
		double m10_before = cvGetSpatialMoment(&moment2_pack, 1, 0);
		double m01_before = cvGetSpatialMoment(&moment2_pack, 0, 1);
		double m00_after = cvGetSpatialMoment(&moment_pack, 0, 0);
		double m10_after = cvGetSpatialMoment(&moment_pack, 1, 0);
		double m01_after = cvGetSpatialMoment(&moment_pack, 0, 1);
		double gX_before = m10_before/m00_before;
		double gY_before = m01_before/m00_before;
		double gX_after = m10_after/m00_after;
		double gY_after = m01_after/m00_after;
		double m00_mallett = cvGetSpatialMoment(&moment_mallett, 0, 0);
		double m10_mallett = cvGetSpatialMoment(&moment_mallett, 1, 0);
		double m01_mallett = cvGetSpatialMoment(&moment_mallett, 0, 1);
		double gX_now_mallett = m10_mallett/m00_mallett;
		double gY_now_mallett = m01_mallett/m00_mallett;
		cvCircle(show_img, cvPoint(gX_before, gY_before), 50, CV_RGB(0,0,255), 6, 8, 0);

		cvLine(show_img, cvPoint(gX_before, gY_before), cvPoint(gX_after, gY_after), cvScalar(0,255,0), 2);
		printf("gX_after: %f\n",gX_after);
		printf("gY_after: %f\n",gY_after);
		printf("gX_before: %f\n",gX_before);
		printf("gY_before: %f\n",gY_before);
		int target_destanceY = 480 - 30;//Y座標の距離を一定にしている。ディフェンスライン。
		//パックの移動は直線のため、一次関数の計算を使って、その後の軌跡を予測する。
		double a_inclination;
		double b_intercept;
		
		
		int closest_frequency;
		
		//reacted limit-switch
		if(gpioRead(24) == 1){
			gpioWrite(18, 0);	
			closest_frequency = gpioSetPWMfrequency(18, 0);
			break;
		}
		
		//pwm output for rotate
		//台の揺れを想定してマージンをとる
		if(abs(gX_after - gX_before) <= 2){//パックが動いてない場合一時停止
			gpioPWM(18, 0);
			closest_frequency = gpioSetPWMfrequency(18, 0);
			a_inclination = 0;
			b_intercept=0;
		}
		else if(gY_after-2 < gY_before ){	//台の中央に戻る
			//本番の台が届いてから実装
			closest_frequency = gpioSetPWMfrequency(18, 0);
			a_inclination = 0;
			b_intercept=0;
		}
		else{
			gpioPWM(18, 128);
			closest_frequency = gpioSetPWMfrequency(18, 2000);
			a_inclination = (gY_after - gY_before) / (gX_after - gX_before);
			b_intercept = gY_after - a_inclination * gX_after;
		}

		printf("a_inclination: %f\n",a_inclination);
		printf("b_intercept: %f\n",b_intercept);
		int target_coordinateX;
		if(a_inclination){
			target_coordinateX = (int)((target_destanceY - b_intercept) / a_inclination);
		}
		else{
			target_coordinateX = 0;
		}
		cvLine(show_img, cvPoint((int)gX_after, (int)gY_after), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
		while(target_coordinateX < 0 || CAM_PIX_WIDTH < target_coordinateX){
			if(target_coordinateX < 0){
				target_coordinateX = -target_coordinateX;
				a_inclination = -a_inclination;
				cvLine(show_img, cvPoint((int)0, (int)b_intercept), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);		
			}
			else if(CAM_PIX_WIDTH < target_coordinateX){
				target_coordinateX = 2 * CAM_PIX_WIDTH - target_coordinateX;
				cvLine(show_img, cvPoint((int)640, (int)640*a_inclination +b_intercept), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
				b_intercept += 2 * 640 * a_inclination;
				a_inclination= -a_inclination;
			}
		}

		printf("target_coordinateX: %d\n",target_coordinateX);
		
		cvLine(show_img, cvPoint(640, target_destanceY), cvPoint(0, target_destanceY), cvScalar(255,255,0), 2);
		cvLine(show_img, cvPoint((int)gX_now_mallett, (int)gY_now_mallett), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,0,255), 2);
		cvPutText (show_img, to_c_char((int)gX_now_mallett), cvPoint(460,30), &font, cvScalar(220,50,50));
		cvPutText (show_img, to_c_char((int)target_coordinateX), cvPoint(560,30), &font, cvScalar(50,220,220));
		int amount_movement = gX_now_mallett - target_coordinateX;

		//2枚の画像比較1回で移動できる量の計算
		int max_amount_movement = CAM_PIX_WIDTH * 0.54 / 1; //CAM_PIX_WIDTH:640, 比較にかかる時間:0.27*2, 端までの移動時間：1s
		int target_direction;
		if(amount_movement > 0){
			if(max_amount_movement < amount_movement){
			    amount_movement = max_amount_movement;
			}
			target_direction = 0;//時計回り
		}
		else if(amount_movement < 0){
			amount_movement = -amount_movement;//正の数にする
			if(max_amount_movement < amount_movement){
				amount_movement = max_amount_movement;
			}
			target_direction = 1;//反時計回り
		}

		//pwm output for delection
		double set_time_millis= 270 * amount_movement / max_amount_movement;//0.27ms*(0~1)
		gpioWrite(19, target_direction);
		
		printf("setting_frequency: %d\n", closest_frequency);
		//gpioSetTimerFunc(0, (int)set_time_millis, pwmReset);

		// 指定したウィンドウ内に画像を表示する
		cvShowImage("Previous Image", img2);
		cvShowImage("Now Image", show_img);
		cvShowImage("pack", dst_img_pack);
		cvShowImage("mallett", dst_img_mallett);
		
		cvReleaseImage (&dst_img_mallett);
		cvReleaseImage (&dst_img_pack);
		cvReleaseImage (&dst_img2_mallett);
		cvReleaseImage (&dst_img2_pack);
		
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }
    dst.release();
    
	gpioTerminate();
    //Clean up used images
    cvReleaseImage(&img);
    cvReleaseImage(&img2);
    cvReleaseImage(&show_img);
    cvReleaseImage(&imgTracking);
	cvReleaseImage(&imgThresh);
	cvReleaseImage(&imgThresh2);

    cvDestroyAllWindows() ;

    return 0;
}
