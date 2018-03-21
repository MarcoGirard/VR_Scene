#pragma once


#include "QObject"
#include "VR_FrameGrabberProcess.h"
#include "VR_BlurProcess.h"
#include "VR_thresholdProcess.h"
#include <QPixmap>
#include <string>

class VR_ImageProcessor : public QObject
{
	Q_OBJECT
private:
	VR_FrameGrabberProcess * frameGrabber;
	VR_BlurProcess * blurProcess;
	VR_thresholdProcess * thresholdProcess;
	QImage rawImage, blurredImage, thresholdedImage, finalImage;

public:
	enum class ProcessedImageLabel {RAW, BLURRED, THRESHOLDED, FINAL };
	VR_ImageProcessor(QObject * parent);
	~VR_ImageProcessor();
	QPixmap getPixmap(VR_ImageProcessor::ProcessedImageLabel imgLabel);


public slots:
	void process();

signals:
	void processDone();
	
};

