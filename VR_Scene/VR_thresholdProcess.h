#pragma once

#include "VR_ImageProcess.h"
#include "VR_ThresholdValues.h"


class VR_ThresholdProcess : public VR_ImageProcess
{
public:
	VR_ThresholdProcess(QObject * parent);
	~VR_ThresholdProcess();

	// Hérité via VR_ImageProcess
	virtual void process(Mat &imgIn, Mat &imgOut) override;
	void rgbToHsv(const uchar &r, const uchar &g, const uchar &b, uchar &h, uchar &s, uchar &v);
	
public slots:
	void updateThresholdValues(VR_ThresholdValues newValues);

private:
	VR_ThresholdValues thresholdValue;
};

