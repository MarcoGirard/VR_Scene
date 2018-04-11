#pragma once
#include "VR_ImageProcess.h"
class VR_BlobProcess :
	public VR_ImageProcess
{
public:
	VR_BlobProcess(QObject * parent);
	~VR_BlobProcess();

	// H�rit� via VR_ImageProcess
	virtual void process(const Mat & imgIn, Mat & imgOut) override;
};

