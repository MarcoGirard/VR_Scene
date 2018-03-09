#pragma once

#include <QObject>
#include <qdialog.h>

class VR_ColorCalibrator : public QDialog
{
	Q_OBJECT

public:
	VR_ColorCalibrator(QWidget *parent);
	~VR_ColorCalibrator();
};
