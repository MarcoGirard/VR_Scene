#pragma once


#include "QObject"
#include "VR_FrameGrabberProcess.h"
#include "VR_BlurProcess.h"
#include "VR_ThresholdProcess.h"
#include "VR_ErodeProcess.h"
#include "VR_BlobProcess.h"
#include <QPixmap>
#include <string>
#include <QPainter>
#include <QPixmap>

//using namespace cv;

class VR_ImageProcessor : public QObject
{
	Q_OBJECT
private:
	VR_FrameGrabberProcess * frameGrabber;
	VR_BlurProcess * blurProcess;
	VR_ThresholdProcess * thresholdProcess;
	VR_ErodeProcess * erodeProcess;
	VR_BlobProcess * blobProcess;
	cv::Mat rawImage, blurredImage, erodedImage, thresholdedImage, finalImage, blobImage;
	QPixmap displayPixmap;
	bool mProcess{ true };
	bool mDetect{ true };
	

public:
	enum class ProcessedImageType { RAW, BLURRED, THRESHOLDED, ERODED, DILATED, FINAL, BLOB };
	VR_ImageProcessor(QObject * parent=nullptr);
	~VR_ImageProcessor();
	QPixmap & getPixmap(VR_ImageProcessor::ProcessedImageType imgLabel);
	QImage mat_to_qimage_ref(cv::Mat &mat, QImage::Format format);
	void disconnect();
	void setProcess(bool process);
	VR_BlobProcess getBlobProcess() { return blobProcess; }

	bool isTracked() { return blobProcess->isTracked(); }

	


public slots:
	void process();
	void updateThresholdValues(VR_ThresholdValues newValues);
	void kernelSizeUpdated(int newKernelSize);
	void toggleBlobDetection();

signals:
	void processDone();
	void newThresholdValues(VR_ThresholdValues newValues);
	void updateKernelSize(int newKernelSize);
	void sendViewerCoordinates(int x, int y, int z);
	
};

