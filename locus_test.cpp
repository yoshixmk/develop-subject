#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <time.h>
#include <stdio.h>
#include <math.h>

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
IplImage* GetThresholdedImage(IplImage* imgHSV, int minH, int maxH, int minS, int maxS, int minV, int maxV){
    IplImage* imgThresh=cvCreateImage(cvGetSize(imgHSV),IPL_DEPTH_8U, 1);
    cvInRangeS(imgHSV, cvScalar(minH,minS,minV), cvScalar(maxH,maxS,maxV), imgThresh);
    return imgThresh;
}

int main(int argc, char* argv[]){
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

  // 指定したウィンドウ内に画像を表示する
  cvShowImage("circle_sample", img);
  cvShowImage("circle_sample2", img2);

    //create a blank image and assgned to 'imgTracking' which has the same size of original video
  frame=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U, 3);
    imgTracking=cvCreateImage(cvGetSize(img),IPL_DEPTH_8U, 3);
    cvZero(imgTracking); //covert the image, 'imgTracking' to black

  cvNamedWindow("Video");

  // Init font
  cvInitFont(&font,CV_FONT_HERSHEY_SIMPLEX|CV_FONT_ITALIC, 0.4,0.4,0,1);

    //while(true){

    cvSmooth(img, frame, CV_GAUSSIAN,3,3); //smooth the original image using Gaussian kernel

    IplImage* imgHSV = cvCreateImage(cvGetSize(frame), IPL_DEPTH_8U, 3);
    cvCvtColor(frame, imgHSV, CV_BGR2HSV); //Change the color format from BGR to HSV
    imgThresh = GetThresholdedImage(imgHSV,minH,maxH,minS,maxS,minV,maxV);
    imgThresh2 = GetThresholdedImage(imgHSV,RminH,RmaxH,RminS,RmaxS,RminV,RmaxV);


    /// Apply the erosion-dilatation operation for filtering
    cvErode( imgThresh, imgThresh, NULL,1 );
    cvDilate( imgThresh, imgThresh, NULL,1 );
    
 CvSeq* contours;  //hold the pointer to a contour in the memory block
 CvSeq* result;   //hold sequence of points of a contour
 CvMemStorage *storage = cvCreateMemStorage(0); //storage area for all contours
  // Position initialization
 RposX = 0;
 RposY = 0;
 RobjectSize = 0;

 //finding all contours in the image (segmentation)
 cvFindContours(imgThresh, storage, &contours, sizeof(CvContour), CV_RETR_EXTERNAL, CV_CHAIN_APPROX_SIMPLE, cvPoint(0,0));
  IplImage* dst_img;
  dst_img = cvCreateImage(cvSize(384, 512), IPL_DEPTH_8U, 3);
 cvDrawContours(img, contours, CV_RGB(255,0,0), CV_RGB(255,0,0), 0, 2);
    cvLine(img, cvPoint(10, 300), cvPoint(50, 50), cvScalar(0,255,0), 2);
    cvPutText (img, tempStr2, cvPoint(150,20), &font, cvScalar(255,255,0));

    cvPutText (img, logStr, cvPoint(20,220), &font, cvScalar(50,220,220));

    cvShowImage("Video", img);

    //Write image to output video
    cvWriteFrame(record,img);

    

    while(1){
      if(cv::waitKey(30) >= 0){
        break;
      }
    }

    //Clean up used images
    cvReleaseImage(&imgHSV);
    cvReleaseImage(&imgThresh);
    cvReleaseImage(&imgThresh2);
    cvReleaseImage(&img);

    cvDestroyAllWindows() ;
    cvReleaseImage(&imgTracking);
  cvReleaseVideoWriter(&record);

    return 0;
}
