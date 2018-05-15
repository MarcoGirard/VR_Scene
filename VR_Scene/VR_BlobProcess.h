#pragma once
#include "VR_ImageProcess.h"
#include <QObject>
class VR_BlobProcess :
	public VR_ImageProcess
{
	
private:
	std::vector<cv::KeyPoint> keypoints;
	bool tracked{ false };
	int mX{ 0 }, mY{ 0 }, mZ{ 0 };

public:
	VR_BlobProcess(QObject * parent = nullptr);
	~VR_BlobProcess();
	int x() { return mX; }
	int y() { return mY; }
	int z() { return mZ; }

	// Hérité via VR_ImageProcess
	virtual void process(const cv::Mat & imgIn, cv::Mat & imgOut) override;
	bool isTracked();


};

