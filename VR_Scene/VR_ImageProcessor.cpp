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
	//connect(this, &VR_ImageProcessor::newThresholdValues, thresholdProcess, &VR_ThresholdProcess::updateThresholdValues);
	//connect(this, &VR_ImageProcessor::updateKernelSize, blurProcess, &VR_BlurProcess::updateKernelSize);
}


VR_ImageProcessor::~VR_ImageProcessor()
{
}

QPixmap VR_ImageProcessor::getPixmap(VR_ImageProcessor::ProcessedImageType frameType)
{
	switch (frameType) {
	case VR_ImageProcessor::ProcessedImageType::RAW : return QPixmap::fromImage(mat_to_qimage_ref(rawImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::BLURRED : return QPixmap::fromImage(mat_to_qimage_ref(blurredImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::THRESHOLDED : return QPixmap::fromImage(mat_to_qimage_ref(thresholdedImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::ERODED : return QPixmap::fromImage(mat_to_qimage_ref(erodedImage, QImage::Format_ARGB32));
		break;
	case VR_ImageProcessor::ProcessedImageType::BLOB : return QPixmap::fromImage(mat_to_qimage_ref(blobImage, QImage::Format_RGB888));
		break;
	case VR_ImageProcessor::ProcessedImageType::FINAL : return QPixmap::fromImage(mat_to_qimage_ref(finalImage, QImage::Format_ARGB32));
		break;
	}
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

void VR_ImageProcessor::setStaticImg(QImage * img)
{
	cv::Mat(img->height(), img->width(), QImage::Format_ARGB32, img->bits(), img->bytesPerLine()).copyTo(rawImage);
	if (!mProcess) {
		process();
	}
}



void VR_ImageProcessor::updateThresholdValues(VR_ThresholdValues newValues)
{
	// Si l'option de process n'est pas activé, je veux moi même partir un process
	// quand je change la valeur du treshold, même chose pour le kernel size 
	thresholdProcess->updateThresholdValues(newValues);
	if (!mProcess) {
		process();
	}
}

void VR_ImageProcessor::kernelSizeUpdated(int newKernelSize)
{
	//emit updateKernelSize(newKernelSize);
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
