#pragma once

#include "VR_ImageProcess.h"
#include "VR_ThresholdValues.h"


class VR_thresholdProcess : public VR_ImageProcess
{
public:
	VR_thresholdProcess(QObject * parent);
	~VR_thresholdProcess();

	// Hérité via VR_ImageProcess
	virtual void process(QImage & imgIn, QImage & imgOut) override;
	virtual QPixmap getPixmap() override;
	void rgbToHsv(const uchar &r, const uchar &g, const uchar &b, uchar &h, uchar &s, uchar &v);
	
public slots:
	void updateThresholdValues(VR_ThresholdValues newValues);

private:
	VR_ThresholdValues thresholdValue;
};

