#pragma once

#include "VR_ImageProcess.h"

class VR_BlurProcess : public VR_ImageProcess
{
public:
	VR_BlurProcess();
	~VR_BlurProcess();

	// Hérité via VR_ImageProcess
	virtual void process(QImage imgIn, QImage imgOut) override;
	virtual QPixmap getPixmap() override;
};

