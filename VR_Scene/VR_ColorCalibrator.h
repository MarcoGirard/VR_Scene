#pragma once

#include <QObject>
#include <qdialog.h>
#include "VR_calibrationWidget.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include "VR_ImageProcess.h"
#include "VR_FrameGrabberProcess.h"
#include "VR_ImageProcessor.h"

class VR_ColorCalibrator : public QDialog
{
	Q_OBJECT

private:
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;
	QWidget * mainWidget;
	QLabel * videoLabel;
	VR_ImageProcessor * imageProcessor;


public:
	VR_ColorCalibrator(QWidget *parent);
	~VR_ColorCalibrator();

public slots:
	void receiveFrame(QPixmap frame);
};
