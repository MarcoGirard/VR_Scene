#pragma once

#include <QAbstractVideoSurface>

class VR_CameraFrameGrabber : public QAbstractVideoSurface
{
	Q_OBJECT
public:
	VR_CameraFrameGrabber(QObject *parent);
	~VR_CameraFrameGrabber();

	// Hérité via QAbstractVideoSurface
	virtual QList<QVideoFrame::PixelFormat> supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType = QAbstractVideoBuffer::NoHandle) const override;
	virtual bool present(const QVideoFrame & frame) override;

signals:
	void frameAvailable(QImage frame);
};
