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
	QCamera cam;
	VR_CameraFrameGrabber * frameGrabber;
	QImage currentFrame;
	Mat qimage_to_mat_ref(QImage &img, int format);

public:
	VR_FrameGrabberProcess(QObject * parent);
	void disconnect();
	
	// Hérité via VR_ImageProcess
	virtual void process(const Mat &imgIn, Mat &imgOut) override;

signals:
	void frameAvailable(QImage frame);
	void startProcess();

private slots:
	void frameReceived(QImage frame);

};

