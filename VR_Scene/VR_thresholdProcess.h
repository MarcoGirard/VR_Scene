#pragma once

#include "VR_ImageProcess.h"

class VR_thresholdProcess : public VR_ImageProcess
{
public:
	VR_thresholdProcess(QObject * parent);
	~VR_thresholdProcess();

	// Hérité via VR_ImageProcess
	virtual void process(QImage & imgIn, QImage & imgOut) override;
	virtual QPixmap getPixmap() override;
};

