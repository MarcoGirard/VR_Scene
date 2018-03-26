#pragma once

#include <qpixmap.h>
#include <opencv2/opencv.hpp>

class VR_ImageProcess : public QObject
{
public:
	VR_ImageProcess(QObject * parent);
	~VR_ImageProcess();

	virtual void process(QImage &imgIn, QImage &imgOut) = 0;
	virtual QPixmap getPixmap() = 0;
};

