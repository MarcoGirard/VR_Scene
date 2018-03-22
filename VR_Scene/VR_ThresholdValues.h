#ifndef VR_THRESHOLDVALUES_H
#define VR_THRESHOLDVALUES_H

#include <QObject>

class VR_ThresholdValues {

public:
	uchar minHue;
	uchar maxHue;
	uchar minSaturation;
	uchar maxSaturation;
	uchar minValue;
	uchar maxValue;
};

#endif //VR_THRESHOLDVALUES