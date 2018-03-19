#pragma once

#include <QWidget>
#include <qtabwidget.h>
#include <qboxlayout.h>
#include <QLabel>

class VR_calibrationWidget : public QWidget
{
	Q_OBJECT
private: 
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;
	QLabel * videoLabel;


public:
	VR_calibrationWidget();
	~VR_calibrationWidget();

public slots:
	void setVideoLabel(QPixmap frame);

};
