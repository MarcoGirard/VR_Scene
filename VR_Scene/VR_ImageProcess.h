#ifndef VR_IMAGEPROCESS_H
#define VR_IMAGEPROCESS_H

#include <opencv2/opencv.hpp>
#include <qpixmap.h>

using namespace cv;


class VR_ImageProcess
{
	
public:
	VR_ImageProcess();
	~VR_ImageProcess();

	virtual void process(Mat imgIn, Mat imgOut) = 0;
	virtual QPixmap getPixmap() = 0;
};

#endif //VR_IMAGEPROCESS