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
#include "VR_ThresholdValues.h"
#include <QSpinBox>
#include <QPushButton>
#include <QFileDialog>
#include <QCheckBox>

using namespace std;

class VR_ColorCalibrator : public QDialog
{
	Q_OBJECT

private:
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;
	QVBoxLayout * thresholdWidgetLayout, * blurWidgetLayout;
	QWidget * mainWidget, * blurWidget, * thresholdWidget;
	QLabel * rawVideoLabel,
		   *blurVideoLabel,
		   *threshVideoLabel,
		   *blurWidgdetLabel,
		   *activeVideoLabel,
		   *erodedVideoLabel,
		   *blobVideoLabel,
	       *trackingStatusLight;
	VR_ImageProcessor imageProcessor;
	QLowHighScrollBar * hueScrollBar;
	QLowHighScrollBar * saturationScrollBar;
	QLowHighScrollBar * valueScrollBar;
	QSpinBox * blurSpinbox;
	VR_ThresholdValues currentThresholdValues;
	QPushButton * saveBtn, * loadBtn;
	unsigned int savedImgCount{ 0 };
	QCheckBox * chkBoxProcess, * chkBoxDetect;
	
	
	VR_ImageProcessor::ProcessedImageType currentFrameType;

	bool tracked{ false };



public:
	VR_ColorCalibrator(QWidget *parent);
	VR_ThresholdValues thresholdValues();
	void loadImage();
	QString getImagePath();
	void process();
	void setIndicatorLightColor(QLabel * label);

signals:
	void newThresholdValues(VR_ThresholdValues newValues);
	void kernelSizeUpdated(int newKernelSize);

public slots:
	void receiveFrame();
	void tabChanged();
	void thresholdValueChanged();
	void newKernelSize();
	void saveImage();
	void processStateChanged();
};
