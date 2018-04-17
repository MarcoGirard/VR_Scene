#pragma once
#include "VR_ImageProcess.h"
class VR_BlobProcess :
	public VR_ImageProcess
{
private:
	std::vector<cv::KeyPoint> keypoints;
	bool tracked{ false };
public:
	VR_BlobProcess(QObject * parent);
	~VR_BlobProcess();

	// Hérité via VR_ImageProcess
	virtual void process(const Mat & imgIn, Mat & imgOut) override;
	bool isTracked();

};

