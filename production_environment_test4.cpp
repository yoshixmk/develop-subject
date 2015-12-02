#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <string.h>
#include <pigpio.h>
#include <sys/time.h>
//#include <wiringPi.h>
//#include <softPwm.h>
#include <float.h>
#include <opencv2/imgproc/imgproc.hpp>
#include <opencv2/highgui/highgui.hpp>

#include </home/pi/develop-subject/pr-equipment/Color/PerspectiveTransformation.h>
#include </home/pi/develop-subject/pr-equipment/Hardware/Camera.h>
#include </home/pi/develop-subject/pr-equipment/Color/HockeyTableMasking.h>

#define CAM_PIX_2HEIGHT (2 * CAM_PIX_HEIGHT)
#define CAM_PIX_WIDTH  160
#define CAM_PIX_HEIGHT 120

void DrawNextContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level            //輪郭のﾚﾍﾞﾙ(階層)
);

double perimeter_max;
CvSeq *max_perimeter_contor;

//各種輪郭の特徴量の取得
void GetContourFeature(CvSeq *Contour) {
    //面積
    double Area = fabs(cvContourArea(Contour, CV_WHOLE_SEQ));
    //周囲長
    double Perimeter = cvArcLength(Contour);
    
    //円形度
    double CircleLevel = 4.0 * CV_PI * Area / (Perimeter * Perimeter);

    //傾いていない外接四角形領域(ﾌｨﾚ径)
    CvRect rect = cvBoundingRect(Contour);

    if(perimeter_max < Perimeter) {
        perimeter_max = Perimeter;
        max_perimeter_contor = Contour;
    }
}

////////////////////////////////////////////////////////////////
//  子の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawChildContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level             //輪郭のﾚﾍﾞﾙ(階層)
) {

    // 輪郭を描画する色の設定
    CvScalar ContoursColor;

    if ((Level % 2) == 1) {
        //白の輪郭の場合､赤で輪郭を描画
        ContoursColor = CV_RGB( 255, 0, 0 );
    } else {
        //黒の輪郭の場合､青で輪郭を描画
        ContoursColor = CV_RGB( 0, 0, 255 );
    }

    //輪郭の描画
    //cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);

    //各種輪郭の特徴量の取得
    GetContourFeature(Contour); //←ｵﾘｼﾞﾅﾙ関数です｡(詳細は後述)

    if (Contour->h_next != NULL)
        //次の輪郭がある場合は次の輪郭を描画
        DrawNextContour(img, Contour->h_next, Level);
    if (Contour->v_next != NULL)
        //子の輪郭がある場合は子の輪郭を描画
        DrawChildContour(img, Contour->v_next, Level + 1);
}

////////////////////////////////////////////////////////////////
//  次の輪郭を描画する｡
////////////////////////////////////////////////////////////////
void DrawNextContour(
    IplImage *img,    //ﾗﾍﾞﾘﾝｸﾞ結果を描画するIplImage(8Bit3chｶﾗｰ)
    CvSeq *Contour, //輪郭へのﾎﾟｲﾝﾀ
    int Level            //輪郭のﾚﾍﾞﾙ(階層)
) {

    // 輪郭を描画する色の設定
    CvScalar ContoursColor;

    if ((Level % 2) == 1) {
        //白の輪郭の場合､赤で輪郭を描画
        ContoursColor = CV_RGB( 255, 0, 0 );
    } else {
        //黒の輪郭の場合､青で輪郭を描画
        ContoursColor = CV_RGB( 0, 0, 255 );
    }

    //輪郭の描画
    //cvDrawContours( img, Contour, ContoursColor, ContoursColor, 0, 2);

    //各種輪郭の特徴量の取得
    GetContourFeature(Contour); //←ｵﾘｼﾞﾅﾙ関数です｡(詳細は後述)

    if (Contour->h_next != NULL)
        //次の輪郭がある場合は次の輪郭を描画
        DrawNextContour(img, Contour->h_next, Level);

    if (Contour->v_next != NULL)
        //子の輪郭がある場合は子の輪郭を描画
        DrawChildContour(img, Contour->v_next, Level + 1);
}

////////////////////////////////////////////////////////////////
//  ﾗﾍﾞﾘﾝｸﾞ処理
////////////////////////////////////////////////////////////////
void cv_Labelling(
    IplImage *src_img,       //入力画像(8Bitﾓﾉｸﾛ)
    IplImage *dst_img        //出力画像(8Bit3chｶﾗｰ)
) {

    CvMemStorage *storage = cvCreateMemStorage (0);
    CvSeq *contours = NULL;

    if (src_img == NULL)
        return;

    // 画像の二値化【判別分析法(大津の二値化)】
    cvThreshold (src_img, src_img, 0, 255, CV_THRESH_BINARY | CV_THRESH_OTSU);

    // 輪郭の検出(戻り値は取得した輪郭の全個数)
    int find_contour_num = cvFindContours (
                               src_img,                     // 入力画像
                               storage,                      // 抽出された輪郭を保存する領域
                               &contours,                  // 一番外側の輪郭へのﾎﾟｲﾝﾀへのﾎﾟｲﾝﾀ
                               sizeof (CvContour),      // ｼｰｹﾝｽﾍｯﾀﾞのｻｲｽﾞ
                               CV_RETR_EXTERNAL,       // 抽出ﾓｰﾄﾞ
                               // CV_RETR_EXTERNAL - 最も外側の輪郭のみ抽出
                               // CV_RETR_LIST - 全ての輪郭を抽出し,ﾘｽﾄに追加
                               // CV_RETR_CCOMP - 全ての輪郭を抽出し,
                               // 二つのﾚﾍﾞﾙを持つ階層構造を構成する.
                               // 1番目のﾚﾍﾞﾙは連結成分の外側の境界線,
                               // 2番目のﾚﾍﾞﾙは穴(連結成分の内側に存在する)の境界線.
                               // CV_RETR_TREE - 全ての輪郭を抽出し,
                               // 枝分かれした輪郭を完全に表現する階層構造を構成する.
                               CV_CHAIN_APPROX_NONE    // CV_CHAIN_APPROX_SIMPLE:輪郭の折れ線の端点を取得
                               // CV_CHAIN_APPROX_NONE: 輪郭の全ての点を取得
                               // Teh-Chinﾁｪｰﾝの近似ｱﾙｺﾞﾘｽﾞﾑ中の一つを適用する
                               // CV_CHAIN_APPROX_TC89_L1
                               // CV_CHAIN_APPROX_TC89_KCOS
                           );

    if (contours != NULL) {
        //処理後画像を0(黒)で初期化
        cvSet(dst_img, CV_RGB( 0, 0, 0 ));
        //輪郭の描画
        DrawNextContour(dst_img, contours, 1);
    }

    cvDrawContours( dst_img, max_perimeter_contor, CV_RGB( 255, 0, 0 ), CV_RGB( 255, 0, 0 ), 0, 2);
        for ( int i = 0; i < max_perimeter_contor->total; i++) {
        CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, max_perimeter_contor, i);
        //std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;
    }
	//輪郭を構成する頂点座標を取得
    /*for ( int i = 0; i < Contour->total; i++) {
        CvPoint *point = CV_GET_SEQ_ELEM (CvPoint, Contour, i);
        //std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;

    }*/
    //ﾒﾓﾘｽﾄﾚｰｼﾞの解放
    cvReleaseMemStorage (&storage);
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

int compare_cvpoint(const void *a, const void *b)
{
	return (*(CvPoint*)a).x - (*(CvPoint*)b).x;
}

double gettimeofday_sec()
{
	struct timeval tv;
	gettimeofday(&tv,NULL);
	return tv.tv_sec + tv.tv_usec * 1e-6;
}

int daikei_process(double start_time, double end, int cnt_freq, int flag)
{

	double now_time = time_time();
	short ch_freq[3] = {1000,1000,1000};
	short ch_freq2[4] = {313,500,1000,1000};
	double time_freq[4] = {0.05, 0.10, 0.15, 0.20};
	int closest_frequency;
	
	if((end - time_freq[cnt_freq] < now_time) && (flag == 1)){
		if(cnt_freq > 0){
			closest_frequency = gpioSetPWMfrequency(25, ch_freq2[cnt_freq]);
			//printf("gensoku_freq: %d\n",ch_freq2[cnt_freq]);
			gpioPWM(25, 128);
			cnt_freq--;
		}
	}
	else if(now_time>=(start_time+time_freq[cnt_freq]) && (flag == 0)){
		if(cnt_freq < 3){
			closest_frequency = gpioSetPWMfrequency(25, ch_freq[cnt_freq]);
			//printf("kasoku_freq: %d\n",ch_freq[cnt_freq]);
			gpioPWM(25, 128);
			cnt_freq++;
		}
				
	}
	return cnt_freq;
}


int main(int argc, char* argv[]) {
    CvMemStorage *contStorage = cvCreateMemStorage(0);
    CvSeq *contours;
    CvTreeNodeIterator polyIterator;
    
    int found = 0;
    int i;
    CvPoint poly_point;
	int fps=30;
	
	//GPIO sample rate
	gpioCfgClock(4, 0, 100);
	
	// ポリライン近似
    CvMemStorage *polyStorage = cvCreateMemStorage(0);
    CvSeq *polys, *poly;

	// OpenCV variables
	CvFont font;
	
    //printf("start!\n");

	//pwm initialize
	if(gpioInitialise() < 0) return -1;
	//pigpio CW/CCW pin setup
	//X:18, Y1:7, Y2:12
	gpioSetMode(18, PI_OUTPUT); 
	gpioSetMode(7, PI_OUTPUT);
	gpioSetMode(12, PI_OUTPUT);
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	gpioSetMode(23, PI_OUTPUT);
	gpioSetMode(24, PI_OUTPUT);
	//limit-switch setup
	gpioSetMode(5, PI_INPUT);
	gpioWrite(5, 0);
	//razupai conection
	gpioSetMode(8, PI_INPUT);

 
	CvCapture* capture_robot_side = cvCaptureFromCAM(0);
	CvCapture* capture_human_side = cvCaptureFromCAM(1);
    if(capture_robot_side == NULL){
		//std::cout << "Robot Side Camera Capture FAILED" << std::endl;
		return -1;
	 }
	if(capture_human_side ==NULL){
		//std::cout << "Human Side Camera Capture FAILED" << std::endl;
		return -1;
	}

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
	//cvNamedWindow("pack", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow("mallet", CV_WINDOW_AUTOSIZE);
	//cvNamedWindow ("Poly", CV_WINDOW_AUTOSIZE);

	//Create trackbar to change brightness
	int iSliderValue1 = 50;
	cvCreateTrackbar("Brightness", "Now Image", &iSliderValue1, 100);
	//Create trackbar to change contrast
	int iSliderValue2 = 50;
	cvCreateTrackbar("Contrast", "Now Image", &iSliderValue2, 100);
	//pack threthold 0, 50, 120, 220, 100, 220
	int iSliderValuePack1 = 46; //80;
	cvCreateTrackbar("minH", "pack", &iSliderValuePack1, 255);
	int iSliderValuePack2 = 70;//106;
	cvCreateTrackbar("maxH", "pack", &iSliderValuePack2, 255);
	int iSliderValuePack3 = 115;//219;
	cvCreateTrackbar("minS", "pack", &iSliderValuePack3, 255);
	int iSliderValuePack4 = 255;//175;
	cvCreateTrackbar("maxS", "pack", &iSliderValuePack4, 255);
	int iSliderValuePack5 = 0;//29;
	cvCreateTrackbar("minV", "pack", &iSliderValuePack5, 255);
	int iSliderValuePack6 = 255;//203;
	cvCreateTrackbar("maxV", "pack", &iSliderValuePack6, 255);
	//mallet threthold 0, 255, 100, 255, 140, 200
	int iSliderValuemallet1 = 25;
	cvCreateTrackbar("minH", "mallet", &iSliderValuemallet1, 255);
	int iSliderValuemallet2 = 44;
	cvCreateTrackbar("maxH", "mallet", &iSliderValuemallet2, 255);
	int iSliderValuemallet3 = 171;//140
	cvCreateTrackbar("minS", "mallet", &iSliderValuemallet3, 255);
	int iSliderValuemallet4 = 255;
	cvCreateTrackbar("maxS", "mallet", &iSliderValuemallet4, 255);
	int iSliderValuemallet5 = 126;
	cvCreateTrackbar("minV", "mallet", &iSliderValuemallet5, 255);
	int iSliderValuemallet6 = 255;
	cvCreateTrackbar("maxV", "mallet", &iSliderValuemallet6, 255);
	
	// 画像ファイルポインタの宣言
	IplImage* img_robot_side = cvQueryFrame(capture_robot_side);
	IplImage* img_human_side = cvQueryFrame(capture_human_side);
	IplImage* img_all_round = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_2HEIGHT), IPL_DEPTH_8U, 3);
	IplImage* tracking_img = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	IplImage* img_all_round2  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	IplImage* show_img  = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	
	cv::Mat mat_frame1;
	cv::Mat mat_frame2;
	cv::Mat dst_img_v;
	cv::Mat dst_bright_cont;
	int iBrightness  = iSliderValue1 - 50;
	double dContrast = iSliderValue2 / 50.0;
	IplImage* dst_img_frame = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
	IplImage* grayscale_img = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 1);
	IplImage* poly_tmp = cvCreateImage( cvGetSize( img_all_round), IPL_DEPTH_8U, 1);
	IplImage* poly_dst = cvCreateImage( cvGetSize( img_all_round), IPL_DEPTH_8U, 3);
	IplImage* poly_gray = cvCreateImage( cvGetSize(img_all_round),IPL_DEPTH_8U,1);

	int rotate_times = 0;
	//IplImage* -> Mat
	mat_frame1 = cv::cvarrToMat(img_robot_side);
	mat_frame2 = cv::cvarrToMat(img_human_side);
	//上下左右を反転。本番環境では、mat_frame1を反転させる
	cv::flip(mat_frame1, mat_frame1, 0); //水平軸で反転（垂直反転）
	cv::flip(mat_frame1, mat_frame1, 1); //垂直軸で反転（水平反転）
	vconcat(mat_frame2, mat_frame1, dst_img_v);

	dst_img_v.convertTo(dst_bright_cont, -1, dContrast, iBrightness); //１枚にした画像をコンバート
	//画像の膨張と縮小
//	cv::Mat close_img;
//	cv::Mat element(3,3,CV_8U, cv::Scalar::all(255));
//	cv::morphologyEx(dst_img_v, close_img, cv::MORPH_CLOSE, element, cv::Point(-1,-1), 3);
//	cv::imshow("morphologyEx", dst_img_v);
//	dst_img_v.convertTo(dst_bright_cont, -1, dContrast, iBrightness); //１枚にした画像をコンバート

	//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
	*img_all_round = dst_bright_cont;

	cv_ColorExtraction(img_all_round, dst_img_frame, CV_BGR2HSV, 0, 54, 77, 255, 0, 255);

	cvCvtColor(dst_img_frame, grayscale_img, CV_BGR2GRAY);
	cv_Labelling(grayscale_img, tracking_img);

	cvCvtColor(tracking_img, poly_gray, CV_BGR2GRAY);

	cvCopy( poly_gray, poly_tmp);
	cvCvtColor( poly_gray, poly_dst, CV_GRAY2BGR);

	//画像の膨張と縮小
	//cvMorphologyEx(tracking_img, tracking_img,)

	// 輪郭抽出
	found = cvFindContours( poly_tmp, contStorage, &contours, sizeof( CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE);

	// ポリライン近似
	polys = cvApproxPoly( contours, sizeof( CvContour), polyStorage, CV_POLY_APPROX_DP, 8, 10);

	cvInitTreeNodeIterator( &polyIterator, ( void*)polys, 10);
	poly = (CvSeq *)cvNextTreeNode( &polyIterator);
	printf("sort before by X\n");
	for( i=0; i<poly->total; i++)
	{
		poly_point = *( CvPoint*)cvGetSeqElem( poly, i);
//		cvCircle( poly_dst, poly_point, 1, CV_RGB(255, 0 , 255), -1);
//		cvCircle( poly_dst, poly_point, 8, CV_RGB(255, 0 , 255));
		//std::cout << "x:" << poly_point.x << ", y:" << poly_point.y  << std::endl;
	}
	//printf("Poly FindTotal:%d\n",poly->total);

	//枠の座標決定
	//左上 の 壁サイド側 upper_left_f
	//左上 の ゴール寄り  upper_left_g
	//右上 の 壁サイド側 upper_right_f
	//右上 の ゴール寄り  upper_right_g
	//左下 の 壁サイド側 lower_left_f
	//左下 の ゴール寄り  lower_left_g
	//右下 の 壁サイド側 lower_right_f
	//右下 の ゴール寄り  lower_right_g
	CvPoint upper_left_f, upper_left_g, upper_right_f, upper_right_g,
			lower_left_f, lower_left_g, lower_right_f, lower_right_g,
			robot_goal_left, robot_goal_right;

	CvPoint frame_points[8];
//	if(poly->total == 8){
//		for( i=0; i<8; i++){
//			poly_point = *( CvPoint*)cvGetSeqElem( poly, i);
//			frame_points[i] = poly_point;
//		}
//		qsort(frame_points, 8, sizeof(CvPoint), compare_cvpoint);
//		printf("sort after by X\n");
//		for( i=0; i<8; i++){
//			std::cout << "x:" << frame_points[i].x << ", y:" << frame_points[i].y  << std::endl;
//		}
//		if(frame_points[0].y < frame_points[1].y){
//			upper_left_f = frame_points[0];
//			lower_left_f = frame_points[1];
//		}
//		else{
//			upper_left_f = frame_points[1];
//			lower_left_f = frame_points[0];
//		}
//		if(frame_points[2].y < frame_points[3].y){
//			upper_left_g = frame_points[2];
//			lower_left_g = frame_points[3];
//		}
//		else{
//			upper_left_g = frame_points[3];
//			lower_left_g = frame_points[2];
//		}
//		if(frame_points[4].y < frame_points[5].y){
//			upper_right_g = frame_points[4];
//			lower_right_g = frame_points[5];
//		}
//		else{
//			upper_right_g = frame_points[5];
//			lower_right_g = frame_points[4];
//		}
//		if(frame_points[6].y < frame_points[7].y){
//			upper_right_f = frame_points[6];
//			lower_right_f = frame_points[7];
//		}
//		else{
//			upper_right_f = frame_points[7];
//			lower_right_f = frame_points[6];
//		}
//	}
//	else{
		//printf("Frame is not 8 Point\n");
		upper_left_f = cvPoint(14, 29);
		upper_right_f =  cvPoint(143, 29);
		lower_left_f = cvPoint(14, 220);
		lower_right_f =  cvPoint(143, 220);

		upper_left_g = cvPoint(20, 22);
		upper_right_g = cvPoint(138, 22);
		lower_left_g =  cvPoint(20, 226);
		lower_right_g = cvPoint(138, 226);

		robot_goal_left = cvPoint(53, 226);
		robot_goal_right = cvPoint(105, 226);

//		cvCopy(img_all_round, show_img);
//		cvLine(show_img, upper_left_f, upper_right_f, CV_RGB( 255, 255, 0 ));
//		cvLine(show_img, lower_left_f, lower_right_f, CV_RGB( 255, 255, 0 ));
//		cvLine(show_img, upper_right_f, lower_right_f, CV_RGB( 255, 255, 0 ));
//		cvLine(show_img, upper_left_f, lower_left_f, CV_RGB( 255, 255, 0 ));
//
//		cvLine(show_img, upper_left_g, upper_right_g, CV_RGB( 0, 255, 0 ));
//		cvLine(show_img, lower_left_g, lower_right_g, CV_RGB( 0, 255, 0 ));
//		cvLine(show_img, upper_right_g, lower_right_g, CV_RGB( 0, 255, 0 ));
//		cvLine(show_img, upper_left_g, lower_left_g, CV_RGB( 0, 255, 0 ));

		//while(1){
			//cvShowImage("Now Image", show_img);
			//cvShowImage ("Poly", poly_dst);
			//if(cv::waitKey(1) >= 0) {
				//break;
			//}
		//}
		//return -1;
//	}
	printf("upper_left_fX:%d, Y:%d\n",upper_left_f.x, upper_left_f.y);
	printf("upper_left_gX:%d, Y:%d\n",upper_left_g.x, upper_left_g.y);
	printf("upper_right_fX:%d,Y:%d\n", upper_right_f.x, upper_right_f.y);
	printf("upper_right_gX:%d, Y:%d\n" , upper_right_g.x, upper_right_g.y);
	printf("lower_left_fX:%d, Y:%d\n", lower_left_f.x, lower_left_f.y);
	printf("lower_left_gX:%d, Y:%d\n", lower_left_g.x, lower_left_g.y);
	printf("lower_right_fX:%d, Y:%d\n", lower_right_f.x, lower_right_f.y);
	printf("lower_right_gX:%d, Y:%d\n", lower_right_g.x, lower_right_g.y);
	printf("robot_goal_left:%d, Y:%d\n", robot_goal_left.x, robot_goal_left.y);
	printf("robot_goal_right:%d, Y:%d\n", robot_goal_right.x, robot_goal_right.y);

    cvReleaseImage(&dst_img_frame);
    cvReleaseImage(&grayscale_img);
    cvReleaseImage(&poly_tmp);
    cvReleaseImage(&poly_gray);

    cvReleaseMemStorage(&contStorage);
    cvReleaseMemStorage(&polyStorage);
	//return 1;
	// Init font
	cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);
	bool is_pushed_decision_button = 1;//もう一方のラズパイ信号にする

	while(1){
		double process_start = time_time();	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////// if文に入るまでにかかる時間が0.1秒くらい
		//決定ボタンが押されたらスタート
		//if(gpioRead(8)==0 && is_pushed_decision_button==1){
			cvCopy(img_all_round, img_all_round2);
			cvCopy(img_all_round, show_img);
			img_robot_side = cvQueryFrame(capture_robot_side);
			img_human_side = cvQueryFrame(capture_human_side);
			
			//robot_sideとimg_human_sideにPerspectiveTransformation.cppを使う
			IplImage* mRobotSideImage = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_HEIGHT), IPL_DEPTH_8U, 3);
			IplImage* mHumanSideImage = cvCreateImage(cvSize(CAM_PIX_WIDTH, CAM_PIX_HEIGHT), IPL_DEPTH_8U, 3);
			//robot
			CvMat *map_matrix;
			CvPoint2D32f src_pnt[4], dst_pnt[4];

			src_pnt[0] = cvPoint2D32f (25, 12);
			src_pnt[1] = cvPoint2D32f (4, 120);
			src_pnt[2] = cvPoint2D32f (154, 120);
			src_pnt[3] = cvPoint2D32f (136, 14);

			dst_pnt[0] = cvPoint2D32f (19, 12);
			dst_pnt[1] = cvPoint2D32f (19, 120);
			dst_pnt[2] = cvPoint2D32f (141, 120);
			dst_pnt[3] = cvPoint2D32f (141, 12);

			map_matrix = cvCreateMat (3, 3, CV_32FC1);
			cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);

			cvWarpPerspective (img_robot_side, mRobotSideImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));
			
			cvCopy(mRobotSideImage, img_robot_side);

			//human
			

			src_pnt[0] = cvPoint2D32f (23, 22);
			src_pnt[1] = cvPoint2D32f (7, 120);
			src_pnt[2] = cvPoint2D32f (154, 120);
			src_pnt[3] = cvPoint2D32f (135, 21);

			dst_pnt[0] = cvPoint2D32f (19, 21);
			dst_pnt[1] = cvPoint2D32f (19, 120);
			dst_pnt[2] = cvPoint2D32f (141, 120);
			dst_pnt[3] = cvPoint2D32f (141, 21);

			map_matrix = cvCreateMat (3, 3, CV_32FC1);
			cvGetPerspectiveTransform (src_pnt, dst_pnt, map_matrix);
			
			cvWarpPerspective (img_human_side, mHumanSideImage, map_matrix, CV_INTER_LINEAR + CV_WARP_FILL_OUTLIERS, cvScalarAll (100));
	
			cvCopy(mHumanSideImage, img_human_side);
			

			
			//IplImage* -> Mat
			mat_frame1 = cv::cvarrToMat(img_robot_side);
			mat_frame2 = cv::cvarrToMat(img_human_side);
			//上下左右を反転。本番環境では、mat_frame1を反転させる
			cv::flip(mat_frame1, mat_frame1, 0); //水平軸で反転（垂直反転）
			cv::flip(mat_frame1, mat_frame1, 1); //垂直軸で反転（水平反転）
			vconcat(mat_frame2, mat_frame1, dst_img_v);

			iBrightness  = iSliderValue1 - 50;
			dContrast = iSliderValue2 / 50.0;
			dst_img_v.convertTo(dst_bright_cont, -1, dContrast, iBrightness); //１枚にした画像をコンバート
			//明るさ調整した結果を変換(Mat->IplImage*)して渡す。その後解放。
			*img_all_round = dst_bright_cont;
			
			//img_all_roundにHockeyTableMasking.cppを使う
			
			int width = CAM_PIX_WIDTH;
			int height = CAM_PIX_HEIGHT;

			int npts[2] = { 4, 8 };
			CvPoint **pts;
		//	CvPoint center_frame_left = cvPoint(11, height);
		//	CvPoint center_frame_right  = cvPoint(155, height);

			pts = (CvPoint **) cvAlloc (sizeof (CvPoint *) * 2);
			pts[0] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 4);
			pts[1] = (CvPoint *) cvAlloc (sizeof (CvPoint) * 8);
			pts[0][0] = cvPoint(0,0);
			pts[0][1] = cvPoint(width,0);
			pts[0][2] = cvPoint(width, height*2);
			pts[0][3] = cvPoint(0, height*2);
			pts[1][0] = cvPoint(13,25);
			pts[1][1] = cvPoint(13,224);
			pts[1][2] = cvPoint(30,236);
			pts[1][3] = cvPoint(128,236);
			pts[1][4] = cvPoint(146,224);
			pts[1][5] = cvPoint(146,25);
			pts[1][6] = cvPoint(128,13);
			pts[1][7] = cvPoint(30,13);

		//    cvLine(src_img, center_frame_left, center_frame_right, CV_RGB( 0, 255, 255 ));
		//    mHockeyTableImage = src_img;
			cvFillPoly(img_all_round, pts, npts, 2, CV_RGB(0, 0, 0));
			//////
			
			mat_frame1.release();
			mat_frame2.release();
			dst_img_v.release();
	
			IplImage* dst_img_mallet = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
			IplImage* dst_img_pack = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
			IplImage* dst_img2_mallet = cvCreateImage(cvGetSize(img_all_round2), IPL_DEPTH_8U, 3);
			IplImage* dst_img2_pack = cvCreateImage(cvGetSize(img_all_round2), IPL_DEPTH_8U, 3);

			cv_ColorExtraction(img_all_round, dst_img_pack, CV_BGR2HSV, iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);
			cv_ColorExtraction(img_all_round, dst_img_mallet, CV_BGR2HSV, iSliderValuemallet1, iSliderValuemallet2, iSliderValuemallet3, iSliderValuemallet4, iSliderValuemallet5, iSliderValuemallet6);
			cv_ColorExtraction(img_all_round2, dst_img2_pack, CV_BGR2HSV, iSliderValuePack1, iSliderValuePack2, iSliderValuePack3, iSliderValuePack4, iSliderValuePack5, iSliderValuePack6);

			//CvMoments moment_mallet;
			CvMoments moment_pack;
			CvMoments moment_mallet;
			CvMoments moment2_pack;
			//cvSetImageCOI(dst_img_mallet, 1);
			cvSetImageCOI(dst_img_pack, 1);
			cvSetImageCOI(dst_img_mallet, 1);
			cvSetImageCOI(dst_img2_pack, 1);

			//cvMoments(dst_img_mallet, &moment_mallet, 0);
			cvMoments(dst_img_pack, &moment_pack, 0);
			cvMoments(dst_img_mallet, &moment_mallet, 0);
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
			double m00_mallet = cvGetSpatialMoment(&moment_mallet, 0, 0);
			double m10_mallet = cvGetSpatialMoment(&moment_mallet, 1, 0);
			double m01_mallet = cvGetSpatialMoment(&moment_mallet, 0, 1);
			double gX_now_mallet = m10_mallet/m00_mallet;
			double gY_now_mallet = m01_mallet/m00_mallet;

			int target_direction = -1; //目標とする向き　時計回り＝1、　反時計回り＝0
			//円の大きさは全体の1/10で描画
			//cvCircle(show_img, cvPoint(gX_before, gY_before), CAM_PIX_HEIGHT/10, CV_RGB(0,0,255), 6, 8, 0);
			//cvCircle(show_img, cvPoint(gX_now_mallet, gY_now_mallet), CAM_PIX_HEIGHT/10, CV_RGB(0,0,255), 6, 8, 0);
			//cvLine(show_img, cvPoint(gX_before, gY_before), cvPoint(gX_after, gY_after), cvScalar(0,255,0), 2);
			//cvLine(show_img, robot_goal_left, robot_goal_right, cvScalar(0,255,255), 2);
			//printf("gX_after: %f\n",gX_after);
			//printf("gY_after: %f\n",gY_after);
			//printf("gX_before: %f\n",gX_before);
			//printf("gY_before: %f\n",gY_before);
			//printf("gX_now_mallet: %f\n",gX_now_mallet);
			//printf("gY_now_mallet: %f\n",gY_now_mallet);
			
			
			int target_destanceY = CAM_PIX_2HEIGHT - 30; //Y座標の距離を一定にしている。ディフェンスライン。
			//パックの移動は直線のため、一次関数の計算を使って、その後の軌跡を予測する。
			double a_inclination;
			double b_intercept;

			int closest_frequency;

			int target_coordinateX;
			int origin_coordinateY;
			int target_coordinateY;

			int left_frame = (upper_left_f.x + lower_left_f.x)/2;
			int right_frame = (upper_right_f.x + lower_right_f.x)/2;

			double y_line = (upper_left_f.y + lower_right_f.y)/3;
			double waiting_position = (robot_goal_left.x + robot_goal_right.x) / 2;	//75がど真ん中になるポジション

			int pack_found_flg;		//プレイヤー側からロボット側にパックがきたとき、1回目の検出なら1を代入、それ以外なら0を代入（1のときのみX軸を動かす）

////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////			
			
			
			//ロボットからプレイヤーにパックを打ち返したとき、またはパックがその位置で静止したとき原点に戻る処理を行う
			if(gY_after - gY_before < -2 || (gY_after - gY_before <= 2 && gY_after - gY_before >= -2) ){ 
				pack_found_flg = 0;							//リセット（プレイヤーからロボットにパックがきたときに再度動き始める）
				//printf("waiting_position:%d\n",waiting_position);
				//printf("return\n");
				if(waiting_position +10 > gX_now_mallet && gX_now_mallet > waiting_position -10)	closest_frequency = gpioSetPWMfrequency(25,100);		//ゴール近辺ならモータの速度を落とす
				else if(waiting_position +40 > gX_now_mallet && gX_now_mallet >waiting_position -40)	closest_frequency = gpioSetPWMfrequency(25,313);	//ゴールに少し近づいてきたら速度を落とす
				else   	closest_frequency = gpioSetPWMfrequency(25, 1000);																							//ゴールから遠い位置にパックがあるなら速度は速い
				int Get = gpioGetPWMfrequency(25);	
				//printf("Get_freq: %d\n",Get);
				gpioPWM(25, 128);
				target_coordinateX = waiting_position;
				//printf("mallet:%f\n",gX_now_mallet);
				//printf("target_direction:%d\n",target_direction);
				if(waiting_position +3 < gX_now_mallet){//+ 10
					target_direction = 0;//反時計回り
				}
				else if(gX_now_mallet < waiting_position -3){//+5
					target_direction = 1;//時計回り
				}
				else{
					gpioPWM(25, 0);
				}
			}
			/*else if(robot_goal_right.x < gX_now_mallet){
				gpioPWM(25, 128);
				closest_frequency = gpioSetPWMfrequency(25, 1000);
				target_direction = 0;//反時計回り
			}
			else if(gX_now_mallet < robot_goal_left.x){
				gpioPWM(25, 128);
				closest_frequency = gpioSetPWMfrequency(25, 1000);
				target_direction = 1;//時計回り
			}*/
			/*else if(gpioRead(8) == 0){//たぶんラズパイからLOWをもらったら、動作停止だと思う
				gpioPWM(25, 0);
			}*/
			else if(gpioRead(26) == 1){//X軸左のリミットに当たったら
				gpioPWM(25, 128);
				closest_frequency = gpioSetPWMfrequency(25, 800);
				target_direction = 1;//時計回り
				printf("X軸左リミット！時計回り\n");
			}
			
			//プレイヤーからロボット側にパックがきたときに、画像処理が一回目ならモータを動かす処理を行う
			else if(gY_after - gY_before > 5 && pack_found_flg != 1){//y_lineはボードの真ん中。防御処理		// 	(y_line < gY_after && y_line > gY_before)	
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////	//モータの稼働までに0.0001秒かかる	

				pack_found_flg=1;		//パックの軌跡検出した
								
				a_inclination = (gY_after - gY_before) / (gX_after - gX_before);
				b_intercept = gY_after - a_inclination * gX_after;
				//一次関数で目標X座標の計算
				if(a_inclination){
					target_coordinateX = (int)((target_destanceY - b_intercept) / a_inclination);
				}
				else{
					target_coordinateX = 0;
				}
				
				double now_time = time_time();							//経過した時間を取得する
				double start_time = now_time;							//開始時間を記憶しておく
				double end;												//パックの軌跡の位置に移動するまでに必要な時間
				int cnt_freq = 0;											//加減速で周波数切り替えをした回数
				
				int pos;													//回転の方向と速度を変更
				int flag_freq=0;											//加減速で周波数切り替えをした回数が3回になったとき、それ以降加速をしない
				int move_dist = target_coordinateX - gX_now_mallet;	//現在のマレットの位置とパックの位置の距離差
				
																						
				if(move_dist < 0)
					target_direction = 0;									//中心より左なら反時計回り
				else 
					target_direction = 1;									//中心より右なら時計回り		
				
				if(move_dist < -50){										//パックの位置がマレットの位置より51以上左の時
					//printf("pos1\n");
					pos=1;
					end = 1.2 * -move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(move_dist < -25){									//パックの位置がマレットの位置より50以下26以上左の時
					//printf("pos2\n");
					pos=2;
					end = 1.2 * -move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(move_dist < -10){									//パックの位置がマレットの位置より25以下11以上左の時
					//printf("pos3\n");
					pos=3;
					end = 1.2 * -move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(move_dist < 0){									//パックの位置がマレットの位置より10以下1以上左の時
					//printf("pos4\n");
					pos=4;
					end = 1.2 * -move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(0 <= move_dist && move_dist < 10 ){				//パックの位置がマレットの位置より0以上9以下右の時
					//printf("pos5\n");
					pos=5;
					end = 1.2 * move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(10 <= move_dist && move_dist < 25){				//パックの位置がマレットの位置より10以上24以下右の時
					//printf("pos6\n");
					pos=6;
					end = 1.2 * move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(25 <= move_dist && move_dist < 50){				//パックの位置がマレットの位置より25以上49以下右の時
					//printf("pos7\n");
					pos=7;
					end = 1.2 * move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				else if(50 <= move_dist){									//パックの位置がマレットの位置より50以上右の時
					//printf("pos8\n");
					pos=8;
					end = 1.2 * move_dist / 100;							//理論値は0.5。現在のマレットの位置と軌跡の位置から移動時間を算出する
				}
				
				end = end + now_time;										//マレットの移動時間
				
				gpioWrite(18, target_direction);							//ドライバXのGPIOにHIGHを入れる
				closest_frequency = gpioSetPWMfrequency(25, 1000);	
				gpioPWM(25, 128);
/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				while(end - now_time >= 0){								//時間がくるまでループ
					
					now_time = time_time(); 								//最新の時間を取得
					if(cnt_freq == 3)	flag_freq = 1;						//周波数切り替えが3回行われているならそれ以降加速処理をさせない
					switch(pos){
						case 1:												//パックの位置がマレットの位置より51以上左の時
							//printf("case1\n");
							cnt_freq = daikei_process(start_time, end, cnt_freq, flag_freq);
							break;
						case 2:												//パックの位置がマレットの位置より25以下11以上左の時
							//printf("case2\n");
							break;
						case 3:												//パックの位置がマレットの位置より25以下11以上左の時
							//printf("case3\n");
							break;
						case 4:												//パックの位置がマレットの位置より10以下1以上左の時
							//printf("case4\n");
							break;
						case 5:												//パックの位置がマレットの位置より0以上9以下右の時
							//printf("case5\n");
							break;
						case 6:												//パックの位置がマレットの位置より10以上24以下右の時
							//printf("case6\n");
							break;
						case 7:												//パックの位置がマレットの位置より25以上49以下右の時
							//printf("case7\n");
							break;
						case 8:												//パックの位置がマレットの位置より50以上右の時
							//printf("case8\n");
							cnt_freq = daikei_process(start_time, end, cnt_freq, flag_freq);
							break;
						default :
							break;
					}
					
				}

				if(target_direction == 0)									//マレットを原点に戻すためにモータの回転方向を逆にする
					target_direction=1;
				else
					target_direction=0;
					
				closest_frequency = gpioSetPWMfrequency(25,14);
				gpioPWM(25, 0);
			}

////////////////////////////////////////////////////////////////////////////////


			if(target_direction != -1){
				gpioWrite(18, target_direction);
			}
			
//			cvShowImage("Now Image", show_img);
//			cvShowImage("pack", dst_img_pack);
//			cvShowImage("mallet", dst_img_mallet);
//			cvShowImage ("Poly", poly_dst);
			
//			cvReleaseImage (&dst_img_mallet);
//			cvReleaseImage (&dst_img_pack);									//処理に0.01~0.02秒くらいかかる
//			cvReleaseImage (&dst_img2_mallet);
//			cvReleaseImage (&dst_img2_pack);

			if(cv::waitKey(1) >= 0) {
				break;
			}
			
/////////////////////////////////////////////////////////////////////////////////
			
		//}
		//else{ //リセット信号が来た場合
		//	is_pushed_decision_button = 0;
		//}
    }
    
    
    gpioTerminate();
    
    cvDestroyAllWindows();
	
	//Clean up used CvCapture*
	cvReleaseCapture(&capture_robot_side);
	cvReleaseCapture(&capture_human_side);
    //Clean up used images
	cvReleaseImage(&poly_dst);
	cvReleaseImage(&tracking_img);
    cvReleaseImage(&img_all_round);
    cvReleaseImage(&img_human_side);
    cvReleaseImage(&img_all_round2);
    cvReleaseImage(&show_img);
    cvReleaseImage(&img_robot_side);

	

    return 0;
}
