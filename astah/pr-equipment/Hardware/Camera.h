#ifndef HARDWARE_CAMERA_H
#define HARDWARE_CAMERA_H

#include <string>
#include <vector>
#include <list>
#include <iostream>
#include <assert.h>

namespace Hardware
{
class Camera
{
private:
	int camera_image;

	int width;

	int height;

	int camera_number;


public:
	void setSize(int width, int height);

	int getCameraImage();

};

}  // namespace Hardware
#endif
