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

QPixmap VR_ImageProcessor::getPixmap()
{
	return QPixmap::fromImage(finalImage);
}

void VR_ImageProcessor::process()
{
	frameGrabber->process(rawImage, rawImage);
	blurProcess->process(rawImage, blurredImage);
	thresholdProcess->process(blurredImage, finalImage);
	emit processDone(QPixmap::fromImage(finalImage));
}
