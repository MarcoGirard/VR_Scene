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
	int *inCur = reinterpret_cast<int*>((uchar*)(imgIn.bits()));
	int *outCur = reinterpret_cast<int*>((uchar*)(imgOut.bits()));
	int *outEnd = outCur + imgIn.width() * imgIn.height();
	int currentPixel;
	uchar r, g, b;
	
	while (outCur < outEnd) {
		currentPixel = *inCur;

		currentPixel = *outCur;
		
		*outCur = (currentPixel ^= 0x00FF0000);
		
		++outCur;
		++inCur;
	}



	//int *outCur = reinterpret_cast<int*>((uchar*)(im.bits()));
	//int *outEnd = outCur + im.width() * im.height();
	//int value;
	//uchar r, g, b;
	//uchar rMin = param1_->lowValue();
	//uchar rMax = param1_->highValue();
	//uchar gMin = param2_->lowValue();
	//uchar gMax = param2_->highValue();
	//uchar bMin = param3_->lowValue();
	//uchar bMax = param3_->highValue();
	//bool keepSource = checkedButtonKeepImage_->isChecked();

	//while (outCur < outEnd) {
	//	value = *outCur;
	//	r = (value & 0x00FF0000) >> 16;
	//	g = (value & 0x0000FF00) >> 8;
	//	b = value & 0x000000FF;

	//	if (r >= rMin && r <= rMax && g >= gMin && g <= gMax && b >= bMin && b <= bMax) {
	//		*outCur = keepSource ? value : 0xFFFFFFFF;
	//	}
	//	else {
	//		*outCur = 0xFF000000;
	//	}
	//	++outCur;
	//}

}

QPixmap VR_thresholdProcess::getPixmap()
{
	return QPixmap();
}
