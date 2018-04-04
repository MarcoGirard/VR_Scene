#pragma once


#include "QObject"
#include "VR_FrameGrabberProcess.h"
#include "VR_BlurProcess.h"
#include "VR_ThresholdProcess.h"
#include "VR_ErodeProcess.h"
#include <QPixmap>
#include <string>

using namespace cv;

class VR_ImageProcessor : public QObject
{
	Q_OBJECT
private:
	VR_FrameGrabberProcess * frameGrabber;
	VR_BlurProcess * blurProcess;
	VR_ThresholdProcess * thresholdProcess;
	VR_ErodeProcess * erodeProcess;
	Mat rawImage, blurredImage, erodedImage, thresholdedImage, finalImage;

public:
	enum class ProcessedImageType { RAW, BLURRED, THRESHOLDED, ERODED, DILATED, FINAL };
	VR_ImageProcessor(QObject * parent);
	~VR_ImageProcessor();
	QPixmap getPixmap(VR_ImageProcessor::ProcessedImageType imgLabel);
	QImage mat_to_qimage_ref(cv::Mat &mat, QImage::Format format);
	void disconnect();
	


public slots:
	void process();
	void updateThresholdValues(VR_ThresholdValues newValues);
	void kernelSizeUpdated(int newKernelSize);

signals:
	void processDone();
	void newThresholdValues(VR_ThresholdValues newValues);
	void updateKernelSize(int newKernelSize);
	
};

