#pragma once

#include "VR_ImageProcess.h"

class VR_BlurProcess : public VR_ImageProcess
{
public:
	VR_BlurProcess(QObject * parent);
	~VR_BlurProcess();

	// Hérité via VR_ImageProcess
	virtual void process(const Mat &imgIn, Mat &imgOut) override;

private:
	int kernelSize{ 3 };

public slots:
	void updateKernelSize(int newKernelSize);



};

