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
IplImage* imgThresh;
IplImage* imgThresh2;
IplImage* frame=0;

//This function threshold the HSV image and create a binary image
IplImage* GetThresholdedImage(IplImage* imgHSV, int minH, int maxH, int minS, int maxS, int minV, int maxV) {
    IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
    cvInRangeS(imgHSV, cvScalar(minH,minS,minV), cvScalar(maxH,maxS,maxV), imgThresh);
    return imgThresh;
}

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
        std::cout << "x:" << point->x << ", y:" << point->y  << std::endl;

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
	//pigpio pulse setup
	//X:25, Y1:23, Y2:24
	gpioSetMode(25, PI_OUTPUT);
	//limit-switch setup
	gpioSetMode(13, PI_INPUT);
 
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
	cvNamedWindow ("Outer Frame", CV_WINDOW_AUTOSIZE);
	
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
	cvCreateTrackbar("minS", "pack", &iSliderValuePack2, 255);
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
		cv::Mat mat_frame1 = cv::cvarrToMat(img_robot_side);
		cv::Mat mat_frame2 = cv::cvarrToMat(img_human_side);
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
		
		//labeling for outer frame detection
		IplImage *img_all_round_gray = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 1);
		IplImage *dst_labelling_img = cvCreateImage(cvGetSize(img_all_round), IPL_DEPTH_8U, 3);
		cvCvtColor(img_all_round, img_all_round_gray, CV_BGR2GRAY);
		cv_Labelling(img_all_round_gray, dst_labelling_img);
		cvReleaseImage (&img_all_round_gray);
		/*cv::Mat eigen_img = cv::cvarrToMat(dst_labelling_img);  // データをMat形式でコピーする

		cv::Mat gray_img;
		cvtColor(eigen_img, gray_img, CV_BGR2GRAY);
		normalize(gray_img, gray_img, 0, 255, cv::NORM_MINMAX);

		std::vector<cv::Point2f> corners;
		goodFeaturesToTrack(gray_img, corners, 80, 0.01, 5);
		std::vector<cv::Point2f>::iterator it_corner = corners.begin();
		for(; it_corner!=corners.end(); ++it_corner) {
			if((it_corner->y < 76 || 345 < it_corner->y) && (it_corner->x < 75 || 690 < it_corner->x) ){
				circle(eigen_img, cv::Point(it_corner->x, it_corner->y), 1, cv::Scalar(0,200,255), -1);
				circle(eigen_img, cv::Point(it_corner->x, it_corner->y), 8, cv::Scalar(0,200,255));
				std::cout << "x:" << it_corner->x << ", y:" << it_corner->y  << std::endl;
			}
		}*/
		
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
		
		//reacted limit-switch
		if(gpioRead(13) == 1){
			gpioWrite(25, 0);	
			closest_frequency = gpioSetPWMfrequency(25, 0);
			break;
		}
		
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
		//2枚の画像比較1回で移動できる量の計算
		int max_amount_movement = CAM_PIX_WIDTH * 0.54 / 1; //比較にかかる時間:0.27*2, 端までの移動時間：1s
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
		gpioWrite(18, target_direction);
		
		printf("setting_frequency: %d\n", closest_frequency);
		//gpioSetTimerFunc(0, (int)set_time_millis, pwmReset);

		// 指定したウィンドウ内に画像を表示する
		cvShowImage("Previous Image", img2);
		cvShowImage("Now Image", show_img);
		cvShowImage("pack", dst_img_pack);
		cvShowImage("mallett", dst_img_mallett);
		cv::imshow("Vertical Concat", dst_img_v);
		cvShowImage ("Outer Frame", dst_labelling_img);
		
		/*cvReleaseImage (&dst_img_mallett);
		cvReleaseImage (&dst_img_pack);
		cvReleaseImage (&dst_img2_mallett);
		cvReleaseImage (&dst_img2_pack);
		cvReleaseImage (&dst_labelling_img);*/
		
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
	cvReleaseImage(&img_all_round);
	cvReleaseCapture(&capture_robot_side);
	cvReleaseCapture(&capture_human_side);
    //Clean up used images
    cvReleaseImage(&img_human_side);
    cvReleaseImage(&img2);
    cvReleaseImage(&show_img);
    cvReleaseImage(&imgTracking);
    cvReleaseImage(&img_robot_side);
	cvReleaseImage(&imgThresh);
	cvReleaseImage(&imgThresh2);

    return 0;
}