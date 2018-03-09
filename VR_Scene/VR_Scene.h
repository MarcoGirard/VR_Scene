#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VR_Scene.h"
#include<qpushbutton.h>
#include<qboxlayout.h>
#include<qwidget.h>
#include<qcombobox.h>
#include<qdialog.h>

class VR_Scene : public QMainWindow
{
	Q_OBJECT

public:
	VR_Scene(QWidget *parent = Q_NULLPTR);

private:
	Ui::VR_SceneClass ui;
	QPushButton * btnColorCalib, * btnSpaceCalib, * btnStartScene;
	QVBoxLayout * mainLayout;
	QWidget * mainWidget;
	QComboBox * camSelection;
	QDialog * colorCalibrator;

private slots:
	void startColorCalibrator();
};
