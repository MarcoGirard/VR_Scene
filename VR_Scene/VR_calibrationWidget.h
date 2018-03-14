#ifndef VR_CALIBRATIONWIDGET_H
#define VR_CALIBRATIONWIDGET_H

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

#endif //VR_CALIBRATIONWIDGET