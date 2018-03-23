#pragma once


#include "QObject"
#include "VR_FrameGrabberProcess.h"
#include "VR_BlurProcess.h"
#include "VR_ThresholdProcess.h"
#include <QPixmap>
#include <string>

class VR_ImageProcessor : public QObject
{
	Q_OBJECT
private:
	VR_FrameGrabberProcess * frameGrabber;
	VR_BlurProcess * blurProcess;
	VR_ThresholdProcess * thresholdProcess;
	QImage rawImage, blurredImage, thresholdedImage, finalImage;

public:
	enum class ProcessedImageType {RAW, BLURRED, THRESHOLDED, FINAL };
	VR_ImageProcessor(QObject * parent);
	~VR_ImageProcessor();
	QPixmap getPixmap(VR_ImageProcessor::ProcessedImageType imgLabel);
	


public slots:
	void process();
	void updateThresholdValues(VR_ThresholdValues newValues);

signals:
	void processDone();
	void newThresholdValues(VR_ThresholdValues newValues);
	
};

