#include "VR_ColorCalibrator.h"

VR_ColorCalibrator::VR_ColorCalibrator(QWidget *parent)
	: QDialog(parent),
	mainWidget{new QWidget()},
	mainLayout{new QHBoxLayout()},
	videoTabs{new QTabWidget()},
	labelTest{new QLabel("test")}
{
	videoTabs->addTab(new QLabel("lol"), "raw");
	videoTabs->addTab(new QLabel("lolololo"), "blur");
	videoTabs->addTab(new QLabel("lol"), "treshold");
	mainLayout->addWidget(videoTabs);
	setLayout(mainLayout);
}

VR_ColorCalibrator::~VR_ColorCalibrator()
{
}
