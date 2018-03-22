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
	/* Cette fonction est pratiquement une copie des fonctions de segmentation
		dans QuickPgrDemo...
	*/

	imgOut = imgIn;
	int *inCur = reinterpret_cast<int*>((uchar*)(imgIn.bits()));
	int *outCur = reinterpret_cast<int*>((uchar*)(imgOut.bits()));
	int *outEnd = outCur + imgIn.width() * imgIn.height();
	int currentPixel;
	uchar r, g, b, h, s, v;


	//uchar hMin = thresholdValue.minHue;
	//uchar hMax = thresholdValue.maxHue;
	//uchar sMin = thresholdValue.minSaturation;
	//uchar sMax = thresholdValue.maxSaturation;
	//uchar vMin = thresholdValue.minValue;
	//uchar vMax = thresholdValue.maxValue;

	uchar hMin = 100;
	uchar hMax = 130;
	uchar sMin = 100;
	uchar sMax = 120;
	uchar vMin = 50;
	uchar vMax = 100;
	
	while (outCur < outEnd) {
		currentPixel = *inCur;
		r = (currentPixel & 0x00FF0000) >> 16;
		g = (currentPixel & 0x0000FF00) >> 8;
		b = (currentPixel & 0x000000FF);

		rgbToHsv(r, g, b, h, s, v);
		
		/* test si le pixel respectent les conditions de segmentation */
		if (h>hMin && h<hMax && s>sMin && s<sMax && v>vMin && v<vMax) {
			*outCur = 0xFFFFFFFF;
		} else {
			*outCur = 0;
		}
		
		++outCur;
		++inCur;
	}
}

QPixmap VR_thresholdProcess::getPixmap()
{
	return QPixmap();
}

void VR_thresholdProcess::rgbToHsv(const uchar & r, const uchar & g, const uchar & b, uchar & h, uchar & s, uchar & v)
{
	// copié de rgb2hsv dans QuickPgrDemo -> colorSpaceTools
	// rgb from 0 to 255
	// hsv results from 0 to 255
	double dr = r / 255.0;
	double dg = g / 255.0;
	double db = b / 255.0;

	double dMin = std::min(std::min(dr, dg), db);			// min value of rgb
	double dMax = std::max(std::max(dr, dg), db);			// max value of rgb

	if (dMax <= 1.0E-5) {									// r = g = b = 0
		h = 0;
		s = 0;
		v = 0;
		return;
	}

	double delta = dMax - dMin;								// delta rgb value 
	if (delta <= 1.0E-5) {									// no chroma...
		h = 0;
		s = 0;
		v = dMax * 255;
		return;
	}

	double dh, ds;

	ds = delta / dMax;

	if (dr == dMax) {
		dh = fmod((dg - db) / delta, 6.0);					// between yellow & magenta
	}
	else if (dg == dMax) {
		dh = 2.0 + (db - dr) / delta;						// between cyan & yellow
	}
	else {
		dh = 4.0 + (dr - dg) / delta;						// between magenta & cyan
	}

	dh /= 6.0;												// normalize 0-1

	if (dh < 0.0) dh += 1.0;
	if (dh > 1.0) dh -= 1.0;

	h = dh * 255;											// rescale 0-255
	s = ds * 255;
	v = dMax * 255;


}

void VR_thresholdProcess::updateThresholdValues(VR_ThresholdValues newValues)
{
	thresholdValue.minHue = newValues.minHue;
	thresholdValue.maxHue = newValues.maxHue;
	thresholdValue.minSaturation = newValues.minSaturation;
	thresholdValue.maxSaturation = newValues.maxSaturation;
	thresholdValue.minValue = newValues.minValue;
	thresholdValue.maxValue = newValues.maxValue;
}


