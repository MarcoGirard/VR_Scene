#pragma once


#include "QObject"
#include "VR_FrameGrabberProcess.h"
#include "VR_BlurProcess.h"
#include "VR_thresholdProcess.h"
#include <QPixmap>

class VR_ImageProcessor : public QObject
{
	Q_OBJECT
private:
	VR_FrameGrabberProcess * frameGrabber;
	VR_BlurProcess * blurProcess;
	VR_thresholdProcess * thresholdProcess;
	QImage rawImage, blurredImage, thresholdedImage, finalImage;

public:
	VR_ImageProcessor(QObject * parent);
	~VR_ImageProcessor();
	QPixmap getPixmap();

public slots:
	void process();

signals:
	void processDone(QPixmap frame);
	
};

