#pragma once

#include <qpixmap.h>
#include <opencv2/opencv.hpp>

//using namespace cv;

class VR_ImageProcess : public QObject
{
public:
	VR_ImageProcess(QObject * parent);
	~VR_ImageProcess();

	virtual void process(const cv::Mat &imgIn, cv::Mat &imgOut) = 0;
};

