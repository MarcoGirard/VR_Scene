#include "VR_BlurProcess.h"



VR_BlurProcess::VR_BlurProcess(QObject * parent) :
	VR_ImageProcess(parent)
{
}


VR_BlurProcess::~VR_BlurProcess()
{
}

void VR_BlurProcess::process(QImage &imgIn, QImage &imgOut)
{
	imgOut = imgIn;
}

QPixmap VR_BlurProcess::getPixmap()
{
	return QPixmap();
}
