#pragma once

#include <QObject>
#include <qdialog.h>
#include "VR_calibrationWidget.h"
#include <qboxlayout.h>
#include <qlabel.h>
#include "VR_ImageProcess.h"
#include "VR_FrameGrabberProcess.h"
#include "VR_ImageProcessor.h"
#include "QLowHighScrollBar.h"
#include <QScrollBar>

class VR_ColorCalibrator : public QDialog
{
	Q_OBJECT

private:
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;
	QVBoxLayout * thresholdWidgetLayout, * blurWidgetLayout;
	QWidget * mainWidget, * blurWidget, * thresholdWidget;
	QLabel * rawVideoLabel, * blurVideoLabel, * threshVideoLabel, * blurWidgdetLabel;
	VR_ImageProcessor * imageProcessor;
	QLowHighScrollBar * hueScrollBar;
	QLowHighScrollBar * saturationScrollBar;
	QLowHighScrollBar * valueScrollBar;
	QScrollBar * blurScrollBar;
	
	VR_ImageProcessor::ProcessedImageLabel currentFrameType;


public:
	VR_ColorCalibrator(QWidget *parent);
	~VR_ColorCalibrator();

public slots:
	void receiveFrame();
	void tabChanged();
};
