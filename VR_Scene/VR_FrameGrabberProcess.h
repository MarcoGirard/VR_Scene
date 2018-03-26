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
	
	// Hérité via VR_ImageProcess
	virtual void process(Mat &imgIn, Mat &imgOut) override;
	virtual QPixmap getPixmap() override;

signals:
	void frameAvailable(QImage frame);
	void startProcess();
private slots:
	void frameReceived(QImage frame);

};

