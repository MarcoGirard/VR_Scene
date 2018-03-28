#include "VR_FrameGrabberProcess.h"

VR_FrameGrabberProcess::VR_FrameGrabberProcess(QObject * parent) :
	VR_ImageProcess(parent),
	cam{new QCamera()},
	frameGrabber{new VR_CameraFrameGrabber(parent)}
{
	cam->setViewfinder(frameGrabber);
	cam->start();

	connect(frameGrabber, &VR_CameraFrameGrabber::frameAvailable, this, &VR_FrameGrabberProcess::frameReceived);
}

void VR_FrameGrabberProcess::process(const Mat &imgIn, Mat &imgOut)
{
	// TO DO 
	//Tester la conversion
	imgOut = qimage_to_mat_ref(currentFrame, QImage::Format_ARGB32);
	// QUESTION POUR JC : Initialisation de mes buffers d'images?
}


// Pris sur http://qtandopencv.blogspot.ca/2013/08/how-to-convert-between-cvmat-and-qimage.html
Mat VR_FrameGrabberProcess::qimage_to_mat_ref(QImage &img, int format)
{
	return cv::Mat(img.height(), img.width(),format, img.bits(), img.bytesPerLine());
}

void VR_FrameGrabberProcess::frameReceived(QImage frame)
{
	QTransform transform;
	transform.rotate(180);

	frame = frame.transformed(transform);
	currentFrame = frame;
	emit startProcess();
}


