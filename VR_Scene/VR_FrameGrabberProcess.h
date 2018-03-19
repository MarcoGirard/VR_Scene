#pragma once
#include "VR_ImageProcess.h"
#include <qobject.h>
#include <qabstractvideosurface.h>
#include <QCamera>
#include <QCameraInfo>
#include <VR_CameraFrameGrabber.h>

class VR_FrameGrabberProcess :
	public VR_ImageProcess
{
	Q_OBJECT	
private:
	QCamera * cam;
	VR_CameraFrameGrabber * frameGrabber;
	QImage currentFrame;
public:
	VR_FrameGrabberProcess(QObject * parent);
	QPixmap getCurrentFrame();

signals:
	void frameAvailable(QImage frame);
private slots:
	void frameReceived(QImage frame);
};

