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
	QVBoxLayout * thresholdWidgetLayout, * blurWidgetLayout, * addWidgetLayout;
	QWidget * mainWidget, * blurWidget, * thresholdWidget;
	QLabel * rawVideoLabel,
		   *blurVideoLabel,
		   *threshVideoLabel,
		   *blurWidgdetLabel,
		   *activeVideoLabel,
		   *erodedVideoLabel,
		   *blobVideoLabel,
	       *trackingStatusLight,
		   *blobInfo;
	VR_ImageProcessor imageProcessor;
	QLowHighScrollBar * hueScrollBar;
	QLowHighScrollBar * saturationScrollBar;
	QLowHighScrollBar * valueScrollBar;
	QSpinBox * blurSpinbox;
	VR_ThresholdValues currentThresholdValues;
	QPushButton * saveBtn;
	unsigned int savedImgCount{ 0 };
	QCheckBox * chkBoxProcess, * chkBoxDetect;
	
	VR_ImageProcessor::ProcessedImageType currentFrameType;

	bool tracked{ false };

public:
	VR_ColorCalibrator(QWidget *parent);
	VR_ThresholdValues thresholdValues();
	QString getImagePath();
	void process();
	void setIndicatorLightColor(QLabel * label);

signals:
	void newThresholdValues(VR_ThresholdValues newValues);
	void kernelSizeUpdated(int newKernelSize);
	void sendViewerCoordinates(int x, int y, int z);

public slots:
	void receiveFrame();
	void tabChanged();
	void thresholdValueChanged();
	void saveImage();
	void processStateChanged();
	void receiveViewerCoordinates(int x, int y, int z);
};
