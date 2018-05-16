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
	int x1{ 0 }, y1{ 0 }, x2{ 0 }, y2{ 0 };
	// DETECTEUR MEMBRE

public:
	VR_BlobProcess(QObject * parent = nullptr);
	~VR_BlobProcess();
	int x() { return mX; }
	int y() { return mY; }
	int z() { return mZ; }
	int getX1() { return x1; }
	int getX2() { return x2; }
	int getY1() { return y1; }
	int getY2() { return y2; }
	int getDistance();

	// Hérité via VR_ImageProcess
	virtual void process(const cv::Mat & imgIn, cv::Mat & imgOut) override;
	bool isTracked();


};

