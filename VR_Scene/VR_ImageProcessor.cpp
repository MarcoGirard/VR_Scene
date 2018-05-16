#include "VR_ImageProcessor.h"



VR_ImageProcessor::VR_ImageProcessor(QObject * parent) :
	QObject(parent),
	frameGrabber{new VR_FrameGrabberProcess(parent)},
	blurProcess{new VR_BlurProcess(parent)},
	thresholdProcess{ new VR_ThresholdProcess(parent) },
	erodeProcess{new VR_ErodeProcess(parent)},
	blobProcess{new VR_BlobProcess(parent)}
{
	connect(frameGrabber, &VR_FrameGrabberProcess::startProcess, this, &VR_ImageProcessor::process);
}


VR_ImageProcessor::~VR_ImageProcessor()
{
}

QPixmap & VR_ImageProcessor::getPixmap(VR_ImageProcessor::ProcessedImageType frameType)
{
	switch (frameType) {
	case VR_ImageProcessor::ProcessedImageType::RAW : displayPixmap.convertFromImage(mat_to_qimage_ref(rawImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::BLURRED : displayPixmap.convertFromImage(mat_to_qimage_ref(blurredImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::THRESHOLDED : displayPixmap.convertFromImage(mat_to_qimage_ref(thresholdedImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::ERODED : displayPixmap.convertFromImage(mat_to_qimage_ref(erodedImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::BLOB: displayPixmap.convertFromImage(mat_to_qimage_ref(blobImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::FINAL : displayPixmap.convertFromImage(mat_to_qimage_ref(finalImage, QImage::Format_ARGB32));;
		break;
	}
	QPainter paint(&displayPixmap);
	paint.setPen(QColor(255, 255, 255, 255));
	paint.drawText(QPoint(blobProcess->x(),blobProcess->y()),"+");
	//paint.drawLine(320, 0, 320, 480);
	return displayPixmap;
}

// Pris sur http://qtandopencv.blogspot.ca/2013/08/how-to-convert-between-cvmat-and-qimage.html
QImage VR_ImageProcessor::mat_to_qimage_ref(cv::Mat & mat, QImage::Format format)
{
	return QImage(mat.data, mat.cols, mat.rows, mat.step, format).copy();
}

void VR_ImageProcessor::disconnect()
{
	frameGrabber->disconnect();
}

void VR_ImageProcessor::setProcess(bool process)
{
	mProcess = process;
}

void VR_ImageProcessor::updateThresholdValues(VR_ThresholdValues newValues)
{
	// Si l'option de process n'est pas activ�, je veux moi m�me partir un process
	// quand je change la valeur du treshold, m�me chose pour le kernel size 
	thresholdProcess->updateThresholdValues(newValues);
	if (!mProcess) {
		process();
	}
}

void VR_ImageProcessor::kernelSizeUpdated(int newKernelSize)
{
	blurProcess->updateKernelSize(newKernelSize);
	if (!mProcess) {
		process();
	}
}

void VR_ImageProcessor::toggleBlobDetection()
{
	if (mDetect) {
		mDetect = false;
	} else {
		mDetect = true;
	}
}



void VR_ImageProcessor::process()
{
	frameGrabber->process(rawImage, rawImage);
	
	blurProcess->process(rawImage, blurredImage);
	if (mProcess) {
		thresholdProcess->process(blurredImage, thresholdedImage);
	}
	//erodeProcess->process(thresholdedImage, erodedImage);
	if (mDetect) {
		blobProcess->process(thresholdedImage, blobImage);
	}
	emit processDone();
}
