#include "VR_CameraFrameGrabber.h"

VR_CameraFrameGrabber::VR_CameraFrameGrabber(QObject *parent)
	: QAbstractVideoSurface(parent)	
{
}

VR_CameraFrameGrabber::~VR_CameraFrameGrabber()
{
}

QList<QVideoFrame::PixelFormat> VR_CameraFrameGrabber::supportedPixelFormats(QAbstractVideoBuffer::HandleType handleType) const
{
	Q_UNUSED(handleType);
	return QList<QVideoFrame::PixelFormat>()
		<< QVideoFrame::Format_ARGB32
		<< QVideoFrame::Format_ARGB32_Premultiplied
		<< QVideoFrame::Format_RGB32
		<< QVideoFrame::Format_RGB24
		<< QVideoFrame::Format_RGB565
		<< QVideoFrame::Format_RGB555
		<< QVideoFrame::Format_ARGB8565_Premultiplied
		<< QVideoFrame::Format_BGRA32
		<< QVideoFrame::Format_BGRA32_Premultiplied
		<< QVideoFrame::Format_BGR32
		<< QVideoFrame::Format_BGR24
		<< QVideoFrame::Format_BGR565
		<< QVideoFrame::Format_BGR555
		<< QVideoFrame::Format_BGRA5658_Premultiplied
		<< QVideoFrame::Format_AYUV444
		<< QVideoFrame::Format_AYUV444_Premultiplied
		<< QVideoFrame::Format_YUV444
		<< QVideoFrame::Format_YUV420P
		<< QVideoFrame::Format_YV12
		<< QVideoFrame::Format_UYVY
		<< QVideoFrame::Format_YUYV
		<< QVideoFrame::Format_NV12
		<< QVideoFrame::Format_NV21
		<< QVideoFrame::Format_IMC1
		<< QVideoFrame::Format_IMC2
		<< QVideoFrame::Format_IMC3
		<< QVideoFrame::Format_IMC4
		<< QVideoFrame::Format_Y8
		<< QVideoFrame::Format_Y16
		<< QVideoFrame::Format_Jpeg
		<< QVideoFrame::Format_CameraRaw
		<< QVideoFrame::Format_AdobeDng;
}

bool VR_CameraFrameGrabber::present(QVideoFrame const & frame)
{
	if (frame.isValid()) {
		QVideoFrame cloneFrame(frame);
		cloneFrame.map(QAbstractVideoBuffer::ReadOnly);
		QImage image(cloneFrame.bits(),
			cloneFrame.width(),
			cloneFrame.height(),
			QVideoFrame::imageFormatFromPixelFormat(cloneFrame.pixelFormat()));
		cloneFrame.unmap();

		// Image format standardization
		if (image.format() != QImage::Format_ARGB32) {
			image = image.convertToFormat(QImage::Format_ARGB32);
		}

		emit frameAvailable(image);
		return true;
	}
	return false;
}