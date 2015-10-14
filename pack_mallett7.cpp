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

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120
#define CAM_PIX_TO_MM 1.4

time_t start,end;

int fps=30;

// OpenCV variables
CvFont font;
IplImage* imgTracking;

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
	gpioWrite(25, 0);
	//gpioSetPWMfrequency(25, 0);
	gpioSetTimerFunc(0, 6000, NULL);
}

int main(int argc, char* argv[]) {
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
	cvNamedWindow("Previous Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Now Image", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("pack", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("mallett", CV_WINDOW_AUTOSIZE);
	cvNamedWindow("Vertical Concat", CV_WINDOW_AUTOSIZE);
	
	//Create trackbar to change brightness
	int iSliderValue1 = 50;
	cvCreateTrackbar("Brightness", "Now Image", &iSliderValue1, 100);
	//Create trackbar to change contrast
	int iSliderValue2 = 50;
	cvCreateTrackbar("Contrast", "Now Image", &iSliderValue2, 100);
	//pack threthold 0, 50, 120, 220, 100, 220
	int iSliderValuePack1 = 54; //80;
	cvCreateTrackbar("minH", "pack", &iSliderValuePack1, 255);
	int iSliderValuePack2 = 84;//106;
	cvCreateTrackbar("maxH", "pack", &iSliderValuePack2, 255);
	int iSliderValuePack3 = 81;//219;
	cvCreateTrackbar("minS", "pack", &iSliderValuePack3, 255);
	int iSliderValuePack4 = 175;//255;
	cvCreateTrackbar("maxS", "pack", &iSliderValuePack4, 255);
	int iSliderValuePack5 = 0;//29;
	cvCreateTrackbar("minV", "pack", &iSliderValuePack5, 255);
	int iSliderValuePack6 = 255;//203;
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
	IplImage* img_robot_side = cvQueryFrame(capture_robot_side);
	IplImage* img_human_side = cvQueryFrame(capture_human_side);
	IplImage* img_all_round = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	IplImage* img2  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	IplImage* show_img  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	//IplImage* -> Mat
	cv::Mat pre_src;
	cv::Mat pre_dst;
	pre_src = cv::cvarrToMat(img_robot_side);
	int iBrightness  = iSliderValue1 - 50;
	double dContrast = iSliderValue2 / 50.0;
	pre_src.convertTo(pre_dst, -1, dContrast, iBrightness); 
	//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
	*img_robot_side = pre_dst;
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
	
	cv::Mat mat_frame1;
	cv::Mat mat_frame2;
	cv::Mat dst_img_v;
	cv::Mat dst_bright_cont;
	int rotate_times = 0;
	while(1){
		img2 = cvCloneImage(img_all_round);
		show_img = cvCloneImage(img_all_round);
		img_robot_side = cvQueryFrame(capture_robot_side);
		img_human_side = cvQueryFrame(capture_human_side);
		//IplImage* -> Mat
		mat_frame1 = cv::cvarrToMat(img_robot_side);
		mat_frame2 = cv::cvarrToMat(img_human_side);
		//上下左右を反転。本番環境では、mat_frame1を反転させる
		cv::flip(mat_frame2, mat_frame2, 0); //水平軸で反転（垂直反転）
		cv::flip(mat_frame2, mat_frame2, 1); //垂直軸で反転（水平反転）
		vconcat(mat_frame2, mat_frame1, dst_img_v);
		
		int iBrightness  = iSliderValue1 - 50;
		double dContrast = iSliderValue2 / 50.0;
		//mat_frame1.convertTo(dst_bright_cont, -1, dContrast, iBrightness); 
		dst_img_v.convertTo(dst_bright_cont, -1, dContrast, iBrightness); //１枚にした画像をコンバート
		//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
		//*img_robot_side = dst_bright_cont;
		*img_all_round = dst_bright_cont;
		mat_frame1.release();
		mat_frame2.release();
		
		// Init font
		cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);
		IplImage* dst_img_mallett = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		IplImage* dst_img_pack = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		IplImage* dst_img2_mallett = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, 3);
		IplImage* dst_img2_pack = cvCreateImage(cvGetSize(img2), IPL_DEPTH_8U, 3);

		cv_ColorExtraction(img_all_round, dst_img_pack, CV_BGR2HSV, iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);
		cv_ColorExtraction(img_all_round, dst_img_mallett, CV_BGR2HSV, iSliderValueMallett1, iSliderValueMallett2, iSliderValueMallett3, iSliderValueMallett4, iSliderValueMallett5, iSliderValueMallett6);
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
		
		//円の大きさは全体の1/10で描画
		cvCircle(show_img, cvPoint(gX_before, gY_before), CAM_PIX_HEIGHT/10, CV_RGB(0,0,255), 6, 8, 0);
		cvLine(show_img, cvPoint(gX_before, gY_before), cvPoint(gX_after, gY_after), cvScalar(0,255,0), 2);
		printf("gX_after: %f\n",gX_after);
		printf("gY_after: %f\n",gY_after);
		printf("gX_before: %f\n",gX_before);
		printf("gY_before: %f\n",gY_before);
		int target_destanceY = CAM_PIX_2HEIGHT - 30;
		//int target_destanceY = CAM_PIX_HEIGHT - 30;//Y座標の距離を一定にしている。ディフェンスライン。
		//パックの移動は直線のため、一次関数の計算を使って、その後の軌跡を予測する。
		double a_inclination;
		double b_intercept;
		
		int closest_frequency;
		
		int target_coordinateX;
		//pwm output for rotate
		//台の揺れを想定してマージンをとる
		if(abs(gX_after - gX_before) <= 1){//パックが動いてない場合一時停止
			gpioPWM(25, 0);
			closest_frequency = gpioSetPWMfrequency(25, 0);
			a_inclination = 0;
			b_intercept=0;
		}
		else if(gY_after-1 < gY_before ){	//packが離れていく時、台の中央に戻る
			//本番の台が届いてから実装
			closest_frequency = gpioSetPWMfrequency(25, 0);
			a_inclination = 0;
			b_intercept=0;
			target_coordinateX = CAM_PIX_WIDTH/2; //目標値は中央
			if(gX_now_mallett < CAM_PIX_WIDTH/2 - CAM_PIX_WIDTH/100){ //壁がとれていないので、CAM_PIX_WIDTH/2=中央 とした
				gpioPWM(25, 128);
				closest_frequency = gpioSetPWMfrequency(25, 2000);
			}
			else{
				gpioPWM(25, 128);
				closest_frequency = gpioSetPWMfrequency(25, 2000);
			}
		}
		else{
			gpioPWM(25, 128);
			closest_frequency = gpioSetPWMfrequency(25, 2000);
			a_inclination = (gY_after - gY_before) / (gX_after - gX_before);
			b_intercept = gY_after - a_inclination * gX_after;
			//一次関数で目標X座標の計算
			if(a_inclination){
				target_coordinateX = (int)((target_destanceY - b_intercept) / a_inclination);
			}
			else{
				target_coordinateX = 0;
			}
		}

		printf("a_inclination: %f\n",a_inclination);
		printf("b_intercept: %f\n",b_intercept);

		cvLine(show_img, cvPoint((int)gX_after, (int)gY_after), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
		while(target_coordinateX < 0 || CAM_PIX_WIDTH < target_coordinateX){
			if(target_coordinateX < 0){
				target_coordinateX = -target_coordinateX;
				a_inclination = -a_inclination;
				cvLine(show_img, cvPoint((int)0, (int)b_intercept), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);		
			}
			else if(CAM_PIX_WIDTH < target_coordinateX){
				target_coordinateX = 2 * CAM_PIX_WIDTH - target_coordinateX;
				cvLine(show_img, cvPoint((int)CAM_PIX_WIDTH, (int)CAM_PIX_WIDTH*a_inclination +b_intercept), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
				b_intercept += 2 * CAM_PIX_WIDTH * a_inclination;
				a_inclination= -a_inclination;
			}
		}

		printf("target_coordinateX: %d\n",target_coordinateX);

		cvLine(show_img, cvPoint(CAM_PIX_WIDTH, target_destanceY), cvPoint(0, target_destanceY), cvScalar(255,255,0), 2);
		cvLine(show_img, cvPoint((int)gX_now_mallett, (int)gY_now_mallett), cvPoint((int)target_coordinateX, target_destanceY), cvScalar(0,0,255), 2);
		cvPutText (show_img, to_c_char((int)gX_now_mallett), cvPoint(460,30), &font, cvScalar(220,50,50));
		cvPutText (show_img, to_c_char((int)target_coordinateX), cvPoint(560,30), &font, cvScalar(50,220,220));
		
		int amount_movement = gX_now_mallett - target_coordinateX;
		int target_direction;
		//reacted limit-switch and target_direction rotate
		if(gpioRead(6) == 1){//X軸右
			gpioPWM(25, 128);	
			closest_frequency = gpioSetPWMfrequency(25, 2000);
			target_direction = 1;//反時計回り
			printf("X軸右リミット！反時計回り\n");
		}
		else if(gpioRead(26) == 1){//X軸左
			gpioPWM(25, 128);
			closest_frequency = gpioSetPWMfrequency(25, 2000);
			target_direction = 0;//時計回り
			printf("X軸左リミット！時計回り\n");
		}
		else if(gpioRead(5) == 1){//Y軸右上
			gpioPWM(23, 128);
			gpioSetPWMfrequency(23, 2000);
			gpioWrite(14, 0);
			printf("Y軸右上リミット！時計回り\n");
		}
		else if(gpioRead(13) == 1){//Y軸右下
			gpioPWM(23, 128);	
			gpioSetPWMfrequency(23, 2000);
			gpioWrite(14, 1);
			printf("Y軸右下リミット！反時計回り\n");
		}
		else if(gpioRead(19) == 1){//Y軸左下
			gpioPWM(24, 128);	
			gpioSetPWMfrequency(24, 2000);
			gpioWrite(15, 0);
			printf("Y軸左下リミット！時計回り\n");
		}
		
		else if(gpioRead(21) == 1){//Y軸左上
			gpioPWM(24, 0);
			gpioSetPWMfrequency(24, 2000);
			gpioWrite(15, 1);
			printf("Y軸左上リミット！反時計回り\n");
		}
		else{
			//Y軸固定のため
			gpioSetPWMfrequency(23, 0);
			gpioSetPWMfrequency(24, 0);
			
			if(amount_movement > 0){
				target_direction = 0;//時計回り
			}
			else if(amount_movement < 0){
				target_direction = 1;//反時計回り
			}
		}
		gpioWrite(18, target_direction);
		
		printf("setting_frequency: %d\n", closest_frequency);

		// 指定したウィンドウ内に画像を表示する
		cvShowImage("Previous Image", img2);
		cvShowImage("Now Image", show_img);
		cvShowImage("pack", dst_img_pack);
		cvShowImage("mallett", dst_img_mallett);
		cv::imshow("Vertical Concat", dst_img_v);
		
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
    //Clean up used cv::Mat
    dst_bright_cont.release();
	dst_img_v.release();
	
	//Clean up used CvCapture*
	cvReleaseCapture(&capture_robot_side);
	cvReleaseCapture(&capture_human_side);
    //Clean up used images
    cvReleaseImage(&img_all_round);
    cvReleaseImage(&img_human_side);
    cvReleaseImage(&img2);
    cvReleaseImage(&show_img);
    cvReleaseImage(&img_robot_side);

    return 0;
}
