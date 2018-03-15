#include "VR_FrameGrabberProcess.h"



VR_FrameGrabberProcess::VR_FrameGrabberProcess(QObject * parent) :
	VR_ImageProcess(parent),
	cam{new QCamera()},
	frameGrabber{new VR_CameraFrameGrabber(parent)}
{
	cam->setViewfinder(frameGrabber);
	cam->start();

	connect(frameGrabber, VR_CameraFrameGrabber::frameAvailable, this, VR_FrameGrabberProcess::frameReceived);
}

QPixmap VR_FrameGrabberProcess::getCurrentFrame()
{
	return QPixmap::fromImage(currentFrame);
}

void VR_FrameGrabberProcess::frameReceived(QImage frame)
{
	currentFrame = frame;
	emit frameAvailable(frame);
}


