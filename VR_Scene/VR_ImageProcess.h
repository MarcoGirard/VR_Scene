#pragma once

#include <qpixmap.h>
class VR_ImageProcess
{
public:
	VR_ImageProcess();
	~VR_ImageProcess();

	virtual void process(Mat imgIn, Mat imgOut) = 0;
	virtual QPixmap getPixmap() = 0;
};

