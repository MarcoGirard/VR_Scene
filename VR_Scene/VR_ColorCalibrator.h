#ifndef VR_COLORCALIBRATION_H
#define VR_COLORCALIBRATION_H

#include <QObject>
#include <qdialog.h>
#include "VR_calibrationWidget.h"
#include <qboxlayout.h>
#include <qlabel.h>

class VR_ColorCalibrator : public QDialog
{
	Q_OBJECT

private:
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;
	QWidget * mainWidget;
	QLabel * labelTest;

public:
	VR_ColorCalibrator(QWidget *parent);
	~VR_ColorCalibrator();

private slots:
	void receiveFrame(QImage frame);
};

#endif //VR_COLORCALIBRATION_H