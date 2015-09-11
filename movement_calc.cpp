#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <math.h>
#include <string.h>

// All units in milimeters
#define robot_center_x 300   // Center of robot
#define robot_center_y 500

#define CAM_PIX_WIDTH 640
#define CAM_PIX_HEIGHT 480
#define CAM_PIX_TO_MM 1.4

time_t start,end;
// 画像ファイルポインタの宣言
IplImage* img=0;
IplImage* img2=0;

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

int main(int argc, char* argv[]) {
    int counter;
    wchar_t auxstr[20];

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

    // 読み込み画像ファイル名
    char imgfile[] = "camera/photodir/cap1.png";
    char imgfile2[] = "camera/photodir/cap2.png";

    // 画像の読み込み
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
    img2 = cvLoadImage(imgfile2, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);

    // 画像の表示用ウィンドウ生成
    cvNamedWindow("circle_sample", CV_WINDOW_AUTOSIZE);
    cvNamedWindow("circle_sample2", CV_WINDOW_AUTOSIZE);

    cvNamedWindow("cv_ColorExtraction");

    // Init font
    cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);

    IplImage* dst_img = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
    IplImage* dst_img2 = cvCreateImage(cvGetSize(img), IPL_DEPTH_8U, 3);
    cv_ColorExtraction(img, dst_img, CV_BGR2HSV, 0, 255, 0, 15, 240, 255);//0,255,0,15,240,255
    cv_ColorExtraction(img2, dst_img2, CV_BGR2HSV, 0, 255, 0, 15, 240, 255);//0,255,0,15,240,255

    CvMoments moments;
    CvMoments moments2;

    if(dst_img -> nChannels == 3 && cvGetImageCOI(dst_img) == 0)
        cvSetImageCOI(dst_img, 1);
    if(dst_img2 -> nChannels == 3 && cvGetImageCOI(dst_img2) == 0)
        cvSetImageCOI(dst_img2, 1);

    cvMoments(dst_img, &moments, 0);
    cvMoments(dst_img2, &moments2, 0);

    double m00_before = cvGetSpatialMoment(&moments, 0, 0);
    double m10_before = cvGetSpatialMoment(&moments, 1, 0);
    double m01_before = cvGetSpatialMoment(&moments, 0, 1);
    double m00_after = cvGetSpatialMoment(&moments2, 0, 0);
    double m10_after = cvGetSpatialMoment(&moments2, 1, 0);
    double m01_after = cvGetSpatialMoment(&moments2, 0, 1);
    double gX_before = m10_before/m00_before;
    double gY_before = m01_before/m00_before;
    double gX_after = m10_after/m00_after;
    double gY_after = m01_after/m00_after;
    cvCircle(img2, cvPoint((int)gX_before, (int)gY_before), 80, CV_RGB(0,0,255), 6, 8, 0);

    cvLine(img2, cvPoint((int)gX_before, (int)gY_before), cvPoint((int)gX_after, (int)gY_after), cvScalar(0,255,0), 2);

	int target_destanceY = 480 - 30;//Y座標の距離を一定にしている。ディフェンスライン。
    //パックの移動は直線のため、一次関数の計算を使って、その後の奇跡を予測する。
    double a_inclination = (gX_after - gX_before) / (gY_after - gY_before);
    double b_intercept = gY_after - a_inclination * gX_after;
    printf("a_inclination: %f\n",a_inclination);
    printf("b_intercept: %f\n",b_intercept);
	int target_coordinateX = (int)((target_destanceY - b_intercept) / a_inclination);
    printf("target_coordinateX: %d\n",target_coordinateX);
    cvLine(img2, cvPoint((int)gX_after, (int)gY_after), cvPoint(target_coordinateX, target_destanceY), cvScalar(0,255,255), 2);
    cvLine(img2, cvPoint(640, target_destanceY), cvPoint(0, target_destanceY), cvScalar(255,255,0), 2);
	cvPutText (img2, to_c_char(target_coordinateX), cvPoint(560,30), &font, cvScalar(50,220,220));
    // 指定したウィンドウ内に画像を表示する
    cvShowImage("circle_sample", img);
    cvShowImage("circle_sample2", img2);

    cvShowImage("cv_ColorExtraction", dst_img);


    while(1) {
        if(cv::waitKey(30) >= 0) {
            break;
        }
    }

    //Clean up used images
    cvReleaseImage(&img);
    cvReleaseImage (&dst_img);

    cvDestroyAllWindows() ;

    return 0;
}
