#pragma once

#include <qpixmap.h>
class VR_ImageProcess
{
public:
	VR_ImageProcess();
	~VR_ImageProcess();

	virtual void process(QImage imgIn, QImage imgOut) = 0;
	virtual QPixmap getPixmap() = 0;
};

