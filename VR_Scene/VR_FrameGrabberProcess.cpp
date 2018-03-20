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

void VR_FrameGrabberProcess::process(QImage &imgIn, QImage &imgOut)
{
	imgOut = currentFrame;
}

QPixmap VR_FrameGrabberProcess::getPixmap()
{
	return QPixmap::fromImage(currentFrame);
}

void VR_FrameGrabberProcess::frameReceived(QImage frame)
{
	QTransform transform;
	transform.rotate(180);

	frame = frame.transformed(transform);
	currentFrame = frame;
	emit startProcess();
}


