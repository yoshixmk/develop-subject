#include <opencv/cv.h>
#include <opencv/highgui.h>
#include "opencv2/imgproc/imgproc.hpp"
#include "opencv2/highgui/highgui.hpp"
#include <iostream>

int main( int argc, char** argv )
{
     // Read original image 
     //Mat src = imread("../camera/photodir/capmallet1.png");
    IplImage* img=0;
    
    // 読み込み画像ファイル名
    char imgfile[] = "../camera/photodir/capmallet1.png";

    // 画像の読み込み
    img = cvLoadImage(imgfile, CV_LOAD_IMAGE_ANYCOLOR | CV_LOAD_IMAGE_ANYDEPTH);
	cv::Mat src = cv::cvarrToMat(img);
	
     //if fail to read the image
     if (!src.data) 
     { 
          std::cout << "Error loading the image\n";
          return -1; 
     }

      // Create a window
     cvNamedWindow("My Window", 1);

     //Create trackbar to change brightness
     int iSliderValue1 = 50;
     cvCreateTrackbar("Brightness", "My Window", &iSliderValue1, 100);

      //Create trackbar to change contrast
     int iSliderValue2 = 50;
     cvCreateTrackbar("Contrast", "My Window", &iSliderValue2, 100);

      while (true)
     {
          //Change the brightness and contrast of the image (For more infomation http://opencv-srf.blogspot.com/2013/07/change-contrast-of-image-or-video.html)
          cv::Mat dst;
          int iBrightness  = iSliderValue1 - 50;
          double dContrast = iSliderValue2 / 50.0;
          src.convertTo(dst, -1, dContrast, iBrightness); 

           //show the brightness and contrast adjusted image
          imshow("My Window", dst);

          // Wait until user press some key for 50ms
          int iKey = cv::waitKey(50);

          //if user press 'ESC' key
          if (iKey == 27)
          {
               break;
          }
     }

      return 0;
}
