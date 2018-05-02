#pragma once
#include "VR_ImageProcess.h"
class VR_ErodeProcess :
	public VR_ImageProcess
{
public:
	VR_ErodeProcess(QObject * parent);
	~VR_ErodeProcess();

	// Hérité via VR_ImageProcess
	virtual void process(const cv::Mat & imgIn, cv::Mat & imgOut) override;
};

