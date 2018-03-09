#pragma once

#include <QWidget>
#include <qtabwidget.h>
#include <qboxlayout.h>

class VR_calibrationWidget : public QWidget
{
	Q_OBJECT
private: 
	QTabWidget * videoTabs;
	QHBoxLayout * mainLayout;


public:
	VR_calibrationWidget();
	~VR_calibrationWidget();


};
