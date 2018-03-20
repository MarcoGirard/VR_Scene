#include "VR_thresholdProcess.h"



VR_thresholdProcess::VR_thresholdProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_thresholdProcess::~VR_thresholdProcess()
{
}

void VR_thresholdProcess::process(QImage & imgIn, QImage & imgOut)
{
	imgOut = imgIn;
}

QPixmap VR_thresholdProcess::getPixmap()
{
	return QPixmap();
}
