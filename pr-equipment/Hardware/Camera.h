#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

#include <pigpio.h>
#include <opencv/cv.h>
#include <opencv/highgui.h>
#include <iostream>

namespace Hardware
{
class Camera
{
private:
	IplImage* mCameraImage;

	int mWidth;

	int mHeight;

	int mCameraNumber;

	CvCapture* mCvCapture;

	static Camera *camera[2];

	Camera(int aCameraNumber);//, int aWidth=160, int aHeight=120);
public:
	 //Camera(const Camera) = delete;
	 //Camera& operator=(const Camera) = delete;

	static Camera get_instance(int aCameraNumber) {
    	if(aCameraNumber == 0){
    		return *camera[0];
    	}
    	else{ //if(aCameraNumber == 1){
    		return *camera[1];
    	}
    	/*else{
    		return (Camera*)NULL;
    	}*/
    }

    static void create(int aCameraNumber) {
        if ( !camera[0] && aCameraNumber==0 ) {
            camera[0] = new Camera(aCameraNumber);
        }
        if ( !camera[1] && aCameraNumber==1 ) {
			camera[1] = new Camera(aCameraNumber);
		}
    }

    static void destroy() {
        if(camera[0]){
        	delete camera[0];
        }
        else if(camera[1]){
        	delete camera[1];
        }
    }

	void setSize(int aWidth, int aHeight);

	IplImage* getCameraImage();
};

}  // namespace Hardware
#endif
