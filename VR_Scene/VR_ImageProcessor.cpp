#include "VR_ImageProcessor.h"



VR_ImageProcessor::VR_ImageProcessor(QObject * parent) :
	QObject(parent),
	frameGrabber{new VR_FrameGrabberProcess(parent)},
	blurProcess{new VR_BlurProcess(parent)},
	thresholdProcess{new VR_ThresholdProcess(parent)}
{

	connect(frameGrabber, &VR_FrameGrabberProcess::startProcess, this, &VR_ImageProcessor::process);
	connect(this, &VR_ImageProcessor::newThresholdValues, thresholdProcess, &VR_ThresholdProcess::updateThresholdValues);
	connect(this, &VR_ImageProcessor::updateKernelSize, blurProcess, &VR_BlurProcess::updateKernelSize);
}


VR_ImageProcessor::~VR_ImageProcessor()
{
}

QPixmap VR_ImageProcessor::getPixmap(VR_ImageProcessor::ProcessedImageType imgLabel)
{
	switch (imgLabel) {
	case VR_ImageProcessor::ProcessedImageType::RAW : return QPixmap::fromImage(rawImage);
		break;
	case VR_ImageProcessor::ProcessedImageType::BLURRED : return QPixmap::fromImage(blurredImage);
		break;
	case VR_ImageProcessor::ProcessedImageType::THRESHOLDED : return QPixmap::fromImage(thresholdedImage);
		break;
	case VR_ImageProcessor::ProcessedImageType::FINAL : return QPixmap::fromImage(finalImage);
		break;
	}
}

void VR_ImageProcessor::updateThresholdValues(VR_ThresholdValues newValues)
{
	emit newThresholdValues(newValues);
}

void VR_ImageProcessor::kernelSizeUpdated(int newKernelSize)
{
	emit updateKernelSize(newKernelSize);
}

void VR_ImageProcessor::process()
{
	frameGrabber->process(rawImage, rawImage);
	blurProcess->process(rawImage, blurredImage);
	thresholdProcess->process(blurredImage, thresholdedImage);
	emit processDone();
}
