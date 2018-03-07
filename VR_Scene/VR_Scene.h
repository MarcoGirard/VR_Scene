#pragma once

#include <QtWidgets/QMainWindow>
#include "ui_VR_Scene.h"

class VR_Scene : public QMainWindow
{
	Q_OBJECT

public:
	VR_Scene(QWidget *parent = Q_NULLPTR);

private:
	Ui::VR_SceneClass ui;
};
