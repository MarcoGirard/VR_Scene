#include "VR_ImageProcessor.h"



VR_ImageProcessor::VR_ImageProcessor(QObject * parent) :
	QObject(parent),
	frameGrabber{new VR_FrameGrabberProcess(parent)},
	blurProcess{new VR_BlurProcess(parent)},
	thresholdProcess{new VR_thresholdProcess(parent)}
{
	connect(frameGrabber, &VR_FrameGrabberProcess::startProcess, this, &VR_ImageProcessor::process);
}


VR_ImageProcessor::~VR_ImageProcessor()
{
}

QPixmap VR_ImageProcessor::getPixmap(VR_ImageProcessor::ProcessedImageLabel imgLabel)
{
	switch (imgLabel) {
	case VR_ImageProcessor::ProcessedImageLabel::RAW : return QPixmap::fromImage(rawImage);
		break;
	case VR_ImageProcessor::ProcessedImageLabel::BLURRED : return QPixmap::fromImage(blurredImage);
		break;
	case VR_ImageProcessor::ProcessedImageLabel::THRESHOLDED : return QPixmap::fromImage(thresholdedImage);
		break;
	case VR_ImageProcessor::ProcessedImageLabel::FINAL : return QPixmap::fromImage(finalImage);
		break;
	}
}

void VR_ImageProcessor::process()
{
	frameGrabber->process(rawImage, rawImage);
	blurProcess->process(rawImage, blurredImage);
	thresholdProcess->process(blurredImage, thresholdedImage);
	emit processDone();
}
