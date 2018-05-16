#include "VR_FrameGrabberProcess.h"

VR_FrameGrabberProcess::VR_FrameGrabberProcess(QObject * parent) :
	VR_ImageProcess(parent),
	//cam{new QCamera(parent)},
	frameGrabber{new VR_CameraFrameGrabber(parent)}
{
	cam.setViewfinder(frameGrabber);
	cam.start();

	connect(frameGrabber, &VR_CameraFrameGrabber::frameAvailable, this, &VR_FrameGrabberProcess::frameReceived);
}

void VR_FrameGrabberProcess::disconnect()
{
	cam.stop();
}

void VR_FrameGrabberProcess::process(const cv::Mat &imgIn, cv::Mat &imgOut)
{
	imgOut = qimage_to_mat_ref(currentFrame, CV_8UC4);
}

// Pris sur http://qtandopencv.blogspot.ca/2013/08/how-to-convert-between-cvmat-and-qimage.html
cv::Mat VR_FrameGrabberProcess::qimage_to_mat_ref(QImage &img, int format)
{
	return cv::Mat(img.height(), img.width(),format, img.bits(), img.bytesPerLine());
}

void VR_FrameGrabberProcess::frameReceived(QImage frame)
{
	// somehow, le frame reçu de la webcam est à l'envers, donc je le tourne avant
	// de l'envoyer plus loin
	QTransform transform;
	transform.rotate(180);

	frame = frame.transformed(transform);
	currentFrame = frame;
	emit startProcess();
}


