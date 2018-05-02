#pragma once

#include "VR_ImageProcess.h"

class VR_BlurProcess : public VR_ImageProcess
{
public:
	VR_BlurProcess(QObject * parent);
	~VR_BlurProcess();

	// Hérité via VR_ImageProcess
	virtual void process(const cv::Mat &imgIn, cv::Mat &imgOut) override;

private:
	double totalR{ 0.0 }, totalG{ 0.0 }, totalB{ 0.0 };
	int imgWidth{ 0 }, imgHeight{ 0 };
	uchar r{ 0 }, g{ 0 }, b{ 0 };
	int currentKernelSize{ 3 };
	int iterationWidth{ 0 };
	int iterationHeight{ 0 };
	int horizontalOffset{ 0 };
	int verticalOffset{ 0 };
	int rowGap{ 0 };

	int const * currentInPixel{ nullptr };
	int * curOut{ nullptr };
	int const * kernelPixel{ nullptr };

	unsigned int initialPointerOffset{ 0 };
	int kernelSize{ 3 };

public slots:
	void updateKernelSize(int newKernelSize);



};

