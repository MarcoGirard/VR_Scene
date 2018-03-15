#pragma once
#include "VR_ImageProcess.h"
#include <qobject.h>
#include <qabstractvideosurface.h>

class VR_FrameGrabber2 : 
	public VR_ImageProcess, public QAbstractVideoSurface
{
public:
	VR_FrameGrabber2();
	~VR_FrameGrabber2();

	// Hérité via QAbstractVideoSurface
	virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
	virtual bool present(const QVideoFrame & frame) override;
};

